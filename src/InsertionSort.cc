/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2008-2020, Alexander Adam					*
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

#include "insertionsort.h"

using namespace inssort;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class InsertionSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class InsertionSort*>( x);
	}
}

const char InsertionSort::m_sort_name[] = "InsertionSort";

InsertionSort::InsertionSort()
{}

InsertionSort::~InsertionSort()
{}

enum bench::SortBase::SpeedGrade InsertionSort::speedGrade()
{
	return bench::SortBase::MEDIUM;
}

const char* InsertionSort::name()
{
	return InsertionSort::m_sort_name;
}

void InsertionSort::sort()
{
	for (bench::feld_t::size_type i = 1; i < feld.size(); ++i)
	{
		insert( feld[ i], i);
	}
}

void InsertionSort::insert( const bench::ele_t e, const bench::feld_t::size_type r)
{
	bench::feld_t::size_type insert_pos = 0;
	// Einfuegeposition finden, mit binaerer Suche
	bench::feld_t::size_type gl = 0,
				 gr = r;

	while ( gr-gl > 1 )
	{
		if (feld[ (gr+gl)/2 ] < e)
			gl = (gr+gl)/2 + 1;
		else
			gr = (gr+gl)/2;
	}

	if ( feld[ gl] <= e )
		insert_pos = gr;
	else
		insert_pos = gl;

	// Elemente um eines nach rechts verschieben, ab Einfuegeposition
	for (bench::feld_t::size_type i = insert_pos; i < r; ++i)
	{
		feld[ i+1] = feld[ i];
	}

	feld[ insert_pos] = e;
}
