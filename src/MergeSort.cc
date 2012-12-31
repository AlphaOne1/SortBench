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

#include "mergesort.h"

using namespace merge;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class MergeSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast<class MergeSort*>(x);
	}
}

const char MergeSort::m_sort_name[] = "MergeSort";

MergeSort::MergeSort()
{}

MergeSort::~MergeSort()
{}

enum bench::SortBase::SpeedGrade MergeSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* MergeSort::name()
{
	return MergeSort::m_sort_name;
}
void MergeSort::sort()
{
	merge_sort( this->feld, 0, this->feld.size()-1);
}

void MergeSort::merge( bench::feld_t& x, const bench::feld_t::size_type a1, const bench::feld_t::size_type e1, const bench::feld_t::size_type a2, const bench::feld_t::size_type e2)
{
	bench::feld_t	tmp( e2-a1+1);	// Temporaeres Feld anlegen
	
	bench::feld_t::size_type
			i1 = a1,	// Linker Quellfeldindex
			i2 = a2,	// Rechter Quellfeldindex
			i3 = 0,		// Zielfeldindex
			te = e1;	// temporaeres Feldende
	
	// Mergen, bis eines der Quellfelder aufgebraucht ist
	while ( (i1 <= e1) && (i2 <= e2) )
	{
		if (x[ i1] <= x[ i2])
			tmp[ i3++] = x[ i1++];
		else
			tmp[ i3++] = x[ i2++];
	}

	// verbleibendes Quellfeld einfach an Zielfeld anhaengen
	if (i2 > e2)
	{
		i1 = i2;
		te = e2;
	}

	while (i1 <= te)
		tmp[ i3++] = x[ i1++];

	// Temporaeres Feld wieder zurueckkopieren
	for (bench::feld_t::size_type i = 0; i < e2-a1+1; ++i)
		x[ a1+i] = tmp[ i];
}

void MergeSort::merge_sort( bench::feld_t& x, const bench::feld_t::size_type anf, const bench::feld_t::size_type end)
{
	if (end-anf >= 1)
	{
		merge_sort( x, anf, (anf+end)/2);
		merge_sort( x, (anf+end)/2+1, end);
	}

	merge( x, anf, (anf+end)/2, (anf+end)/2+1, end);
}

void MergeSort::post()
{}
