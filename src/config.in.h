/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2012-2013, Alexander Adam					*
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

#cmakedefine USE_GETTEXT
#cmakedefine USE_QT

namespace bench {
/*! LOCATIONS contains the locations of each of the sorting modules
 */
const char* LOCATIONS [] = {	@BinaryTreeSort_LOCATION@,
				@BubbleSort_LOCATION@,
				@CombSort_LOCATION@,
				@CountingSort_LOCATION@,
				@HeapSort_LOCATION@,
				@InsertionSort_LOCATION@,
				@MergeSort_LOCATION@,
				@MinMaxSort_LOCATION@,
				@QuickSort_LOCATION@,
				@RadixSort_LOCATION@,
				@SelectionSort_LOCATION@,
				@ShellSort_LOCATION@,
				@STLSort_LOCATION@,
				@StoogeSort_LOCATION@,
				NULL
};
}
#endif /* __CONFIG_IN_H__ */
