// vim: ts=8:sw=8:cindent
/********************************************************************************
*										*
*  Copyright (c) 2007-2012, Alexander Adam					*
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

#include <map>

#include "countingsort.h"

using namespace countsort;

extern "C"
{
	/*!
	 * Erzeugt ein CountingSort-Object und liefert es als SortBase-Zeiger
	 * zurueck.
	 */
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class CountingSort());
	}

	/*!
	 * Nimmt ein SortBase-Objekt entgegen und versucht es in einen
	 * CountingSort-Zeiger zu konvertieren. Eine Pruefung ist nicht notwendig,
	 * da die Programmstruktur nicht mehrere gleichzeitig geladene
	 * Sortierklassen zulaesst.
	 */
	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class CountingSort*>( x);
	}
}

const char CountingSort::m_sort_name[] = "CountingSort";

//! Konstruktor, der nur Basiskonstruktor aufruft
CountingSort::CountingSort()
{}

//! Destruktor, der nichts tut
CountingSort::~CountingSort()
{}

enum bench::SortBase::SpeedGrade CountingSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* CountingSort::name()
{
	return CountingSort::m_sort_name;
}

/*!Sortierfunktion.
 * Der CountingSort ist hier so abgewandelt, dass kein Array fuer die Speicherung der vorhandenen
 * Elemente verwendet wird, sondern eine std::map, das macht den Algorithmus dann auch gleich
 * recht langsam, Das Ablaufen der std::map erfordert, da sie oft mit einem Rot-Schwarz-Baum
 * implementiert wird, wieder O(n log n) Durchgaenge.
 */
void CountingSort::sort()
{
	std::map< bench::ele_t, bench::feld_t::size_type> elements;

	for (bench::feld_t::size_type i = 0; i < feld.size(); ++i)
	{
		elements[ feld[ i]]++;
	}

	bench::feld_t::size_type global = 0;
	for (std::map< bench::ele_t, bench::feld_t::size_type>::iterator it = elements.begin();
		it != elements.end();
		++it )
	{
		for (bench::feld_t::size_type i = 0; i < it->second; ++i)
		{
			feld[ global++] = it->first;
		}
	}
}

//! Leere Post-Funktion
void CountingSort::post()
{}
