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

#include <algorithm>

#include "stlsort.h"

using namespace esteel;

extern "C"
{
	/*!
	 * Erzeugt ein STLSort-Object und liefert es als SortBase-Zeiger
	 * zurueck.
	 */
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class STLSort());
	}

	/*!
	 * Nimmt ein SortBase-Objekt entgegen und versucht es in einen
	 * STLSort-Zeiger zu konvertieren. Eine Pruefung ist nicht notwendig,
	 * da die Programmstruktur nicht mehrere gleichzeitig geladene
	 * Sortierklassen zulaesst.
	 */
	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class STLSort*>( x);
	}
}

const char STLSort::m_sort_name[] = "STLSort";

//! Konstruktor, der nur Basiskonstruktor aufruft
STLSort::STLSort()
{}

//! Destruktor, der nichts tut
STLSort::~STLSort()
{}

enum bench::SortBase::SpeedGrade STLSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* STLSort::name()
{
	return STLSort::m_sort_name;
}

//! Sortierfunktion, die std::sort() aufruft
void STLSort::sort()
{
	std::sort( feld.begin(), feld.end());
}

//! Leere Post-Funktion
void STLSort::post()
{}
