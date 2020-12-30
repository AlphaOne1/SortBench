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

#include "quicksort.h"

using namespace quick;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class QuickSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class QuickSort*>( x);
	}
}

const char QuickSort::m_sort_name[] = "QuickSort";

QuickSort::QuickSort()
{}

QuickSort::~QuickSort()
{}

enum bench::SortBase::SpeedGrade QuickSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* QuickSort::name()
{
	return QuickSort::m_sort_name;
}

void QuickSort::sort()
{
	this->quicksort( 0, feld.size()-1);
}

void QuickSort::quicksort( const bench::feld_t::size_type lg, const bench::feld_t::size_type rg)
{
	if (lg >= rg)
		return;
	
	bench::ele_t pivot = feld[ rg];

	bench::feld_t::size_type	l = lg-1;
	bench::feld_t::size_type	r = rg;
	
	while (true)
	{
		while (  feld[ ++l] < pivot )
		{}
		while ( (feld[ --r] > pivot) && (r > l) )
		{}

		if ( l >= r )
			break;

		std::swap( feld[ l], feld[ r]);
	}
	std::swap( feld[ l], feld[ rg]);

	if (l)
		quicksort( lg, l-1);
	if (l != rg)
		quicksort( l+1, rg);
}

void QuickSort::post()
{}
