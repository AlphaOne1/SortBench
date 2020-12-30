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

#include "stoogesort.h"

using namespace stooge;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class StoogeSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class StoogeSort*>( x);
	}
}

const char StoogeSort::m_sort_name[] = "StoogeSort";

StoogeSort::StoogeSort()
{}

StoogeSort::~StoogeSort()
{}

enum bench::SortBase::SpeedGrade StoogeSort::speedGrade()
{
	return bench::SortBase::VERY_SLOW;
}

const char* StoogeSort::name()
{
	return StoogeSort::m_sort_name;
}

void StoogeSort::sort()
{
	stooge_sort( this->feld, 0, this->feld.size()-1);
}

void StoogeSort::stooge_sort( bench::feld_t& x, bench::feld_t::size_type anf, bench::feld_t::size_type end)
{
	bench::ele_t	zw;

	if (feld[ anf] > feld[ end])
	{
		zw		= feld[ anf];
		feld[ anf]	= feld[ end];
		feld[ end]	= zw;
	}

	if ( (end-anf) < 2 )
		return;

	stooge_sort( x, anf,			end - (end-anf+1)/3);
	stooge_sort( x, anf + (end-anf+1)/3,	end);
	stooge_sort( x, anf,			end - (end-anf+1)/3);
}

void StoogeSort::post()
{}
