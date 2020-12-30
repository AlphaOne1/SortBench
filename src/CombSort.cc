/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2012-2020, Alexander Adam					*
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

#include "combsort.h"

using namespace combsort;

extern "C"
{
	/*!
	 * Erzeugt ein CombSort-Object und liefert es als SortBase-Zeiger
	 * zurueck.
	 */
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class CombSort());
	}

	/*!
	 * Nimmt ein SortBase-Objekt entgegen und versucht es in einen
	 * CombSort-Zeiger zu konvertieren. Eine Pruefung ist nicht notwendig,
	 * da die Programmstruktur nicht mehrere gleichzeitig geladene
	 * Sortierklassen zulaesst.
	 */
	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class CombSort*>( x);
	}
}

const char CombSort::m_sort_name[] = "CombSort";

//! Konstruktor, der nur Basiskonstruktor aufruft
CombSort::CombSort()
{}

//! Destruktor, der nichts tut
CombSort::~CombSort()
{}

enum bench::SortBase::SpeedGrade CombSort::speedGrade()
{
	return bench::SortBase::MEDIUM;
}

const char* CombSort::name()
{
	return CombSort::m_sort_name;
}

//! Sortierfunktion
void CombSort::sort()
{
	const double			step	= 1.247330950103979;
	bool				swapped	= false;
	bench::feld_t::size_type	gap	= this->feld.size();

	while (gap > 1 || swapped)
	{
		gap = (double)gap / step;
		swapped = false;

		if (gap == 9 || gap == 10)
			gap = 11;
		else if ( gap < 1 )
			gap = 1;

		// Es wird laut Algo wirklich nur ein Durchlauf gemacht!
		for (bench::feld_t::size_type j = 0; j+gap < this->feld.size(); ++j)
		{
			if (feld[ j] > feld[ j+gap])
			{
				std::swap( feld[ j], feld[ j+gap]);
				swapped = true;
			}
		}
	}
}

//! Leere Post-Funktion
void CombSort::post()
{}
