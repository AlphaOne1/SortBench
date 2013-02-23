/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2008-2013, Alexander Adam					*
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

#include "selectionsort.h"

using namespace selsort;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class SelectionSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class SelectionSort*>( x);
	}
}

const char SelectionSort::m_sort_name[] = "SelectionSort";

SelectionSort::SelectionSort()
{}

SelectionSort::~SelectionSort()
{}

enum bench::SortBase::SpeedGrade SelectionSort::speedGrade()
{
	return bench::SortBase::SLOW;
}

const char* SelectionSort::name()
{
	return SelectionSort::m_sort_name;
}

void SelectionSort::sort()
{
	bench::feld_t::size_type	small_pos;
	bench::ele_t			small_ele;

	for (bench::feld_t::size_type ipos = 0; ipos < feld.size(); ++ipos)
	{
		small_pos = ipos;
		small_ele = feld[ ipos];

		for (bench::feld_t::size_type i = ipos+1; i < feld.size(); ++i)
		{
			if (feld[ i] < small_ele)
			{
				small_pos = i;
				small_ele = feld[ i];
			}
		}

		feld[ small_pos]= feld[ ipos];
		feld[ ipos]	= small_ele;
	}
}

