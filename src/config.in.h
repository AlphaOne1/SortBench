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

#ifndef __CONFIG_IN_H__
#define __CONFIG_IN_H__

#include <cstddef>

#cmakedefine USE_INTL
#cmakedefine USE_QT

namespace bench {
/*! LOCATIONS contains the locations of each of the sorting modules
 */
const char* LOCATIONS [] = {	"$<TARGET_FILE:BinaryTreeSort>",
				"$<TARGET_FILE:BubbleSort>",
				"$<TARGET_FILE:CombSort>",
				"$<TARGET_FILE:CountingSort>",
				"$<TARGET_FILE:HeapSort>",
				"$<TARGET_FILE:InsertionSort>",
				"$<TARGET_FILE:MergeSort>",
				"$<TARGET_FILE:MinMaxSort>",
				"$<TARGET_FILE:QuickSort>",
				"$<TARGET_FILE:RadixSort>",
				"$<TARGET_FILE:SelectionSort>",
				"$<TARGET_FILE:ShellSort>",
				"$<TARGET_FILE:STLSort>",
				"$<TARGET_FILE:StoogeSort>",
				NULL
};
}

/*
 * gettext specific defines
 */
#ifndef USE_INTL
	#define gettext(s) (s)
	#define ngettext(s, ps, n) ( (n > 1) ? (ps) : (s) )
#else
	#define LOCALE_DIR @Locale_LOCATION@
#endif /* USE_INTL */

#endif /* __CONFIG_IN_H__ */
