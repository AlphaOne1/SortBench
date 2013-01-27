// vim: ts=8:sw=8:cindent
/********************************************************************************
*										*
*  Copyright (c) 2007-2013, Alexander Adam					*
*										*
*  All rights reserved.								*
*										*
*  Redistribution and use in source and binary forms, with or without		*
*  modification, are permitted provided that the following conditions are met:	*
*										*
*	-	Redistributions of source code must retain the above copyright	*
*		notice, this list of conditions and the following disclaimer.	*
*	-	Redistributions in binary form must reproduce the above		*
*		copyright notice, this list of conditions and the following	*
*		disclaimer in the documentation and/or other materials provided	*
*		with the distribution.						*
*	-	The names of its contributors may be used to endorse or promote	*
*		products derived from this software without specific prior	*
*		written permission.						*
*										*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS		*
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT		*
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	*
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER	*
*  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,	*
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,		*
*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR		*
*  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF	*
*  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING		*
*  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS		*
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.			*
*										*
********************************************************************************/

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

#ifndef _MSC_VER
	#include <sys/time.h>
	#include <dlfcn.h>
#else
	#include <ctime>
	#include <stdint.h>
	#include <windows.h>
#endif /* _MSC_VER */

#include "bench.h"
#include "sortbase.h"

using namespace bench;

#ifdef _MSC_VER
namespace {
	/*!
	 * last_error_string gibt die Stringrepraesentation des letzten aufgetretenen Fehlers unter
	 * Windows zurueck.
	 * 	\return	std::string-Repraesentation des letzten aufgetretenen Fehlers
	 */
	std::string last_error_string()
	{
		DWORD error_code = GetLastError();
		LPSTR error_string;
		std::string ret;

		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
			       FORMAT_MESSAGE_FROM_SYSTEM,
			       NULL,
			       error_code,
			       0,
			       LPTSTR( &error_string),
			       0,
			       NULL);

		ret = error_string;

		LocalFree( error_string);
		return ret;
	}

	/*!
	 * Dies ist _keine_ Funktion, die gettimeofday von UNIX ersetzt. Sie kann nur im Kontext dieses
	 * Benchmarks eingesetzt werden, um die Zeit, die vergeht zu messen. Ihre Ergebnisse koennen nicht
	 * in eine absolute Zeit umgerechnet werden! Das timeval struct ist unter Windows bereits aus der
	 * Socket-API vorhanden und muss damit nicht erneut definiert werden.
	 *	\param	tv	enthaelt bei Rueckkehr das Ergebnis
	 *	retval	0	immer
	 */
	inline int gettimeofday( struct timeval *tv, int*)
	{
		LARGE_INTEGER	f, t;
		const uint64_t	*fi = (uint64_t*)&f,
				*ti = (uint64_t*)&t;

		if (!QueryPerformanceCounter( &t))
		{
			std::cerr << "Error measuring time:" << std::endl
				  << last_error_string() << std::endl;
			std::exit( EXIT_FAILURE);
		}

		if (!QueryPerformanceFrequency( &f))
		{
			std::cerr << "Error measuring timer frequency:" << std::endl
				  << last_error_string() << std::endl;
			std::exit( EXIT_FAILURE);
		}

		tv->tv_sec = *ti / *fi;
		tv->tv_usec = (*ti % *fi) * 1000000 / *fi;

		return 0;
	}
}
#endif /* _MSC_VER */

/*!
 * Konstruktor des Benchmarks.
 *	\param	size	Groesse des zu sortierenden Feldes
 *	\param	seed	Startwert fuer den Zufallszahlengenerator
 */
Bench::Bench( int size, int seed)
{
	this->reference.resize( size);
	
	std::srand( seed);
	for (size_t i = 0; i < reference.size(); ++i)
		reference[ i] = std::rand(); // % 100;

	this->create	= NULL;
	this->destroy	= NULL;
	this->dlhandle	= NULL;
	this->aktmod	= NULL;
	this->aktmodname= "";
	this->found_bad = false;
}

/*!
 * Destruktor des Benchmarks
 */
Bench::~Bench()
{
	if (this->aktmod)
	{
		this->unloadmod();
	}
}

/*!
 * Mit dieser Funktion ist der Grad der (Un-)Ordnung einstellbar.
 * \param	ordnung	Grad der Ordnung, je weiter an 100 desto geordneter wird
 * 			das Feld sein.
 */
void Bench::init( const int ordnung)
{
	if (!ordnung)
	{
		return;
	}
	else
	{
		int blocksize = (int)(reference.size() * (ordnung / 100.0));
					
		for (size_t i = 0; i < reference.size() / blocksize; ++i)
		{
			std::sort(	reference.begin() + i * blocksize,
					reference.begin() + (i+1) * blocksize - 1);
		}
		std::sort(	reference.begin() + (reference.size() / blocksize) * blocksize,
				reference.end() );
	}
}

/*!
 * Gibt den Grad der (Un-)Ordnung zurueck.
 *	\return	Grad der Unordnung (0=rueckwaerts sortiert, 1000 ist vorsortiert)
 */
int Bench::getOrdnung() const
{
	int cnt = 0;
	
	for (size_t i = 0; i < reference.size()-1; ++i)
		if (reference[ i] < reference[ i+1])
			cnt++;
	return (int)((float)cnt / reference.size() * 1000);
}

/*!
 * Gibt den Namen des aktuell geladenen Modules zurueck.
 *	\return	Name des aktuell geladenen Modules
 */
std::string Bench::getAktModName() const
{
	return this->aktmod->name();
}

/*!
 * Diese Funktion misst die Zeit, die das gerade geladene Modul fuer die
 * Sortierung des Referenzfeldes benoetigt.
 *	\return	Zeit in Mikrosekunden
 */
long int Bench::test()
{
	if (this->aktmod == NULL)
	{
		std::cerr << "Somebody called the test function without having a module loaded!" << std::endl;
		std::exit( EXIT_FAILURE);
	}

	struct timeval start, ende;
	
	gettimeofday( &start, 0);
	this->aktmod->sort();
	gettimeofday( &ende, 0);
	
	this->aktmod->post();

	if (!this->aktmod->test())
	{
		std::cerr << "The module " << aktmodname << " does not sort right!" << std::endl;
		this->found_bad = true;
		this->aktmod->output( std::cout);
	}

	return (ende.tv_sec*1000000 + ende.tv_usec) - (start.tv_sec*1000000 + start.tv_usec);
}

/*!
 * Diese Funktion sagt aus, ob der gerade geteste Algorithmus richtig lief.
 *	\retval true wenn richtig
 *	\retval false wenn fehlerhaft
 */
bool Bench::badSorter() const
{
	return this->found_bad;
}

/*!
 * Diese Funktion laedt eine dynamische Bibliothek.
 *	\param	modname	Name der dynamischen Bibliothek, die geladen werden soll.
 */
void Bench::loadmod( std::string modname)
{
#ifndef _MSC_VER
	union Caster	cast;
#endif /* _MSC_VER */
	this->found_bad = false;

	if (aktmod || create || destroy)
	{
		std::cerr << "Somebody called the loader function with having another module loaded!" << std::endl;
		std::exit( EXIT_FAILURE);
	}
	
	this->aktmodname = modname;
	
#ifndef _MSC_VER
	if( (this->dlhandle = dlopen( aktmodname.c_str(), RTLD_NOW )) == NULL)
	{
		std::cerr << "Error loading the module: " << aktmodname << std::endl
			  << dlerror() << std::endl;
		std::exit( EXIT_FAILURE);
	}

	cast.obj_in	= (void*)dlsym( dlhandle, "create");
	this->create	= (create_t)cast.fn_out;
#else
	this->dlhandle = LoadLibrary( aktmodname.c_str());
	if (this->dlhandle == NULL)
	{
		std::cerr << "Error loading the module: " << this->aktmodname << std::endl
			  << last_error_string() << std::endl;
		std::exit( EXIT_FAILURE);
	}

	this->create	= (bench::create_t)GetProcAddress( this->dlhandle, "create");
#endif /* _MSC_VER */
	

	if (this->create == NULL)
	{
		std::cerr << "Error loading destroy: "
#ifndef _MSC_VER
			  << dlerror()
#else
			  << last_error_string()
#endif /* _MSC_VER */
			  << std::endl;
		std::exit( EXIT_FAILURE);
	}

#ifndef _MSC_VER
	cast.obj_in	= (void*)dlsym( dlhandle, "destroy");
	this->destroy	= (destroy_t)cast.fn_out;
#else
	this->destroy	= (destroy_t)GetProcAddress( this->dlhandle, "destroy");
#endif /* _MSC_VER */

	if (this->destroy == NULL)
	{
		std::cerr << "Error loading create: "
#ifndef _MSC_VER
			  << dlerror()
#else
			  << last_error_string()
#endif /* _MSC_VER */
			  << std::endl;		std::exit( EXIT_FAILURE);
	}

	this->aktmod = this->create();
	this->aktmod->pre( this->reference);
}

/*!
 * Diese Funktion entlaedt das gerade geladene Modul wieder.
 */
void Bench::unloadmod()
{
	if (!(aktmod && create && destroy))
	{
		std::cerr << "Somebody called the unload function withouth having a module loaded!" << std::endl;
		std::exit( EXIT_FAILURE);
	}
	
	destroy( this->aktmod);

#ifndef _MSC_VER
	if (dlclose(this->dlhandle))
	{
		std::cerr << "Error unloading the module: " << aktmodname << std::endl
			  << dlerror() << std::endl;
		std::exit( EXIT_FAILURE);
	}
#else
	if ( !FreeLibrary( this->dlhandle))
	{
		std::cerr << "Error unloading the module: " << aktmodname << std::endl
			  << last_error_string() << std::endl;
		std::exit( EXIT_FAILURE);
	}
#endif /* _MSC_VER */

	this->dlhandle	= NULL;
	this->aktmod	= NULL;
	this->aktmodname= "";
	
	this->create	= NULL;
	this->destroy	= NULL;
}

