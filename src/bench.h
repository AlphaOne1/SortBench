/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2007-2020, Alexander Adam					*
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

/*! \file bench.h
 * In dieser Datei befindet sich die Deklaration fuer die Benchmarkklasse.
 */

#ifndef __BENCH_H__
#define __BENCH_H__

#include <string>

#ifdef _MSC_VER
	#include <Windows.h>
#endif /* _MSC_VER */

#include "sortbase.h"

namespace bench
{
	/*!
	 * Basisklasse fuer den Benchmark. Sie nimmt die Zeitmessungen vor und
	 * ist fuer das Laden und Entladen von Modulen verantwortlich.
	 */
	class Bench
	{
		public:			Bench		( int, int);
					~Bench		();
			void		init		( const int);
			std::string	getAktModName	() const;
			int		getOrdnung	() const;

			long int	test		();
			bool		badSorter	() const;

			void		loadmod		( std::string);
			void		unloadmod	();
				
		protected:
			feld_t		reference;	//!< Referenzfeld
			int		ordnung;	//!< (Un-)Sortiertheit des Referenzfeldes
			bool		found_bad;	//!< true, wenn ein Algorithmus falsch laeuft
			
			std::string	aktmodname;	//!< Name des aktuell geladenen Modules
			class SortBase*	aktmod;		//!< Zeiger auf das aktuell geladenen Modul

#ifndef _MSC_VER
			void*		dlhandle;	//!< Handle fuer aktuell geladene dyn. Bibliothek
#else
			HMODULE		dlhandle;	//!< Handle fuer aktuell geladene dyn. Bibliothek
#endif /* _MSC_VER */

			create_t	create;		//!< Zeiger auf Erstellerfunktion der dyn. Bibliothek
			destroy_t	destroy;	//!< Zeiger auf Destruktorfunktion der dyn. Bibliothek
	};
}

#endif /*__BENCH_H__*/
