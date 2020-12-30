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

#include "minmaxsort.h"

using namespace minmaxsort;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class MinMaxSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class MinMaxSort*>( x);
	}
}

const char MinMaxSort::m_sort_name[] = "MinMaxSort";

MinMaxSort::MinMaxSort()
{}

MinMaxSort::~MinMaxSort()
{}

enum bench::SortBase::SpeedGrade MinMaxSort::speedGrade()
{
	return bench::SortBase::SLOW;
}

const char* MinMaxSort::name()
{
	return MinMaxSort::m_sort_name;
}

void MinMaxSort::sort()
{
	bench::feld_t::size_type	small_pos;
	bench::ele_t			small_ele;
	bench::feld_t::size_type	big_pos;
	bench::ele_t			big_ele;

	for (bench::feld_t::size_type imin = 0, imax = feld.size()-1; imin < imax; ++imin, --imax)
	{
		small_pos	= imin;
		small_ele	= feld[ imin];

		big_pos		= imax;
		big_ele		= feld[ imax];

		for (bench::feld_t::size_type i = imin; i <= imax; ++i)
		{
			if (feld[ i] < small_ele)
			{
				small_pos = i;
				small_ele = feld[ i];
			}
			if (feld[ i] > big_ele)
			{
				big_pos = i;
				big_ele = feld[ i];
			}
		}

		if (small_pos == imax)
		{
			if (big_pos == imin)
			{
				feld[ small_pos]= big_ele;
				feld[ big_pos]	= small_ele;
			}
			else
			{
				feld[ small_pos]	= feld[ imin];
				feld[ imin]		= small_ele;

				feld[ big_pos]		= feld[ imax];
				feld[ imax]		= big_ele;
			}
		}
		else
		{
			feld[ big_pos]		= feld[ imax];
			feld[ imax]		= big_ele;
			
			feld[ small_pos]	= feld[ imin];
			feld[ imin]		= small_ele;
		}
	}
}

