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

#include "radixsort.h"

using namespace radixsort;

extern "C"
{
	/*!
	 * Erzeugt ein RadixSort-Object und liefert es als SortBase-Zeiger
	 * zurueck.
	 */
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class RadixSort());
	}

	/*!
	 * Nimmt ein SortBase-Objekt entgegen und versucht es in einen
	 * RadixSort-Zeiger zu konvertieren. Eine Pruefung ist nicht notwendig,
	 * da die Programmstruktur nicht mehrere gleichzeitig geladene
	 * Sortierklassen zulaesst.
	 */
	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class RadixSort*>( x);
	}
}

const char RadixSort::m_sort_name[] = "RadixSort";

//! Konstruktor, der nur Basiskonstruktor aufruft
RadixSort::RadixSort()
{}

//! Destruktor, der nichts tut
RadixSort::~RadixSort()
{}

enum bench::SortBase::SpeedGrade RadixSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* RadixSort::name()
{
	return RadixSort::m_sort_name;
}

//! Sortierfunktion
void RadixSort::sort()
{
	rsort( 0, feld.size()-1, sizeof( bench::ele_t)*8-1);
}

//! Radixtales Sortieren
void RadixSort::rsort( const bench::feld_t::size_type r, const bench::feld_t::size_type l, const bench::feld_t::size_type bpos)
{
	bench::feld_t::size_type	pr = r,
					pl = l;

	const unsigned long		mask = 1 << bpos;

	while (pr < pl)
	{
		while (pr < pl)
		{
			if (feld[ pr] & mask)
				break;
			++pr;
		}

		while (pl > pr)
		{
			if (! (feld[ pl] & mask) )
				break;
			--pl;
		}

		if (pr < pl)
		{
			bench::ele_t tmp = feld[ pr];
			feld[ pr] = feld[ pl];
			feld[ pl] = tmp;
			++pr;
			--pl;
		}
	}

	if (bpos > 0)
	{
		const bench::feld_t::size_type prm1 = pr != 0 ? pr-1 : 0;
		const bench::feld_t::size_type prp1 = pr+1 != (bench::feld_t::size_type)-1 ? pr+1 : pr;

		if (feld[ pr] & mask)
		{
			if (r < prm1)
				rsort( r, prm1, bpos-1);
			if (pr < l)
				rsort( pr, l, bpos-1);
		}
		else
		{
			if (r < pr)
				rsort( r, pr, bpos-1);
			if (prp1 < l)
				rsort( prp1, l, bpos-1);
		}
	}
}

void RadixSort::post()
{}
