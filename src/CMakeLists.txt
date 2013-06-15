# vim: set ts=8 sw=8 autoindent smartindent: ####################################
#										#
#  Copyright (c) 2007-2013, Alexander Adam					#
#										#
#  All rights reserved.								#
#										#
#  Redistribution and use in source and binary forms, with or without		#
#  modification, are permitted provided that the following conditions are met:	#
#										#
#  	-	Redistributions of source code must retain the above copyright	#
#		notice, this list of conditions and the following disclaimer.	#
#  	-	Redistributions in binary form must reproduce the above		#
#		copyright notice, this list of conditions and the following	#
#		disclaimer in the documentation and/or other materials provided	#
#		with the distribution.						#
#  	-	The names of its contributors may be used to endorse or promote	#
#		products derived from this software without specific prior	#
#		written permission.						#
#										#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS		#
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT		#
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	#
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER	#
#  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,	#
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,		#
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR		#
#  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF	#
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING		#
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS		#
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.			#
#										#
#################################################################################

ADD_EXECUTABLE	( sortbench
			Bench.cc
			Main.cc
		)

# Externalizing of the SortBase is necessary because Windows does not allow
# for libraries to call code from the executable
ADD_LIBRARY	( SortBase SHARED
			SortBase.cc
			sortbase.h
		)

IF (WIN32)
	TARGET_LINK_LIBRARIES	( sortbench
					SortBase
				)
ELSE(WIN32) 
	TARGET_LINK_LIBRARIES	( sortbench
					SortBase
					dl
				)
ENDIF(WIN32)

SET( FAST_ALGO_TEST_SIZE 1000000)
SET( SLOW_ALGO_TEST_SIZE 26000)
SET( BAD_ALGO_TEST_SIZE  1500)

#################################################################################
##	Fast Algorithms							       ##
#################################################################################

ADD_LIBRARY	( BinaryTreeSort MODULE
			BinaryTreeSort.cc
			binarytreesort.h
		)
TARGET_LINK_LIBRARIES	( BinaryTreeSort SortBase )
ADD_TEST	( NAME binary_tree_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:BinaryTreeSort>
		)
GET_TARGET_PROPERTY( BinaryTreeSort_LOCATION BinaryTreeSort LOCATION)
SET( BinaryTreeSort_LOCATION \"${BinaryTreeSort_LOCATION}\")

ADD_LIBRARY	( CombSort MODULE
			CombSort.cc
			combsort.h
		)
TARGET_LINK_LIBRARIES	( CombSort SortBase)
ADD_TEST	( NAME comb_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:CombSort>
		)
GET_TARGET_PROPERTY( CombSort_LOCATION CombSort LOCATION)
SET( CombSort_LOCATION \"${CombSort_LOCATION}\")

ADD_LIBRARY	( CountingSort MODULE
			CountingSort.cc
			countingsort.h
		)
TARGET_LINK_LIBRARIES	( CountingSort SortBase )
ADD_TEST	( NAME counting_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:CountingSort>
		)
GET_TARGET_PROPERTY( CountingSort_LOCATION CountingSort LOCATION)
SET( CountingSort_LOCATION \"${CountingSort_LOCATION}\")


ADD_LIBRARY	( HeapSort MODULE
			HeapSort.cc
			heapsort.h
		)
TARGET_LINK_LIBRARIES	( HeapSort SortBase )
ADD_TEST	( NAME heap_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:HeapSort>
		)
GET_TARGET_PROPERTY( HeapSort_LOCATION HeapSort LOCATION)
SET( HeapSort_LOCATION \"${HeapSort_LOCATION}\")

ADD_LIBRARY	( MergeSort MODULE
			MergeSort.cc
			mergesort.h
		)
TARGET_LINK_LIBRARIES	( MergeSort SortBase )
ADD_TEST	( NAME merge_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:MergeSort>
		)
GET_TARGET_PROPERTY( MergeSort_LOCATION MergeSort LOCATION)
SET( MergeSort_LOCATION \"${MergeSort_LOCATION}\")

ADD_LIBRARY	( QuickSort MODULE
			QuickSort.cc
			quicksort.h
		)
TARGET_LINK_LIBRARIES	( QuickSort SortBase )
ADD_TEST	( NAME quick_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:QuickSort>
		)
GET_TARGET_PROPERTY( QuickSort_LOCATION QuickSort LOCATION)
SET( QuickSort_LOCATION \"${QuickSort_LOCATION}\")

ADD_LIBRARY	( RadixSort MODULE
			RadixSort.cc
			radixsort.h
		)
TARGET_LINK_LIBRARIES	( RadixSort SortBase )
ADD_TEST	( NAME radix_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:RadixSort>
		)
GET_TARGET_PROPERTY( RadixSort_LOCATION RadixSort LOCATION)
SET( RadixSort_LOCATION \"${RadixSort_LOCATION}\")

ADD_LIBRARY	( STLSort MODULE
			STLSort.cc
			stlsort.h
		)
TARGET_LINK_LIBRARIES	( STLSort SortBase )
ADD_TEST	( NAME stl_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:STLSort>
		)
GET_TARGET_PROPERTY( STLSort_LOCATION STLSort LOCATION)
SET( STLSort_LOCATION \"${STLSort_LOCATION}\")

#################################################################################
##	Slow Algorithms							       ##
#################################################################################

ADD_LIBRARY	( BubbleSort MODULE
			BubbleSort.cc
			bubblesort.h
		)
TARGET_LINK_LIBRARIES	( BubbleSort SortBase )
ADD_TEST	( NAME bubble_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:BubbleSort>
		)
GET_TARGET_PROPERTY( BubbleSort_LOCATION BubbleSort LOCATION)
SET( BubbleSort_LOCATION \"${BubbleSort_LOCATION}\")

ADD_LIBRARY	( InsertionSort MODULE
			InsertionSort.cc
			insertionsort.h
		)
TARGET_LINK_LIBRARIES	( InsertionSort SortBase )
ADD_TEST	( NAME insertion_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:InsertionSort>
		)
GET_TARGET_PROPERTY( InsertionSort_LOCATION InsertionSort LOCATION)
SET( InsertionSort_LOCATION \"${InsertionSort_LOCATION}\")

ADD_LIBRARY	( MinMaxSort MODULE
			MinMaxSort.cc
			minmaxsort.h
		)
TARGET_LINK_LIBRARIES	( MinMaxSort SortBase )
ADD_TEST	( NAME minmax_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:MinMaxSort>
)
GET_TARGET_PROPERTY( MinMaxSort_LOCATION MinMaxSort LOCATION)
SET( MinMaxSort_LOCATION \"${MinMaxSort_LOCATION}\")

ADD_LIBRARY	( SelectionSort MODULE
			SelectionSort.cc
			selectionsort.h
		)
TARGET_LINK_LIBRARIES	( SelectionSort SortBase )
ADD_TEST	( NAME selection_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:SelectionSort>
		)
GET_TARGET_PROPERTY( SelectionSort_LOCATION SelectionSort LOCATION)
SET( SelectionSort_LOCATION \"${SelectionSort_LOCATION}\")

ADD_LIBRARY	( ShellSort MODULE
			ShellSort.cc
			shellsort.h
		)
TARGET_LINK_LIBRARIES	( ShellSort SortBase )
ADD_TEST	( NAME shell_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:ShellSort>
		)
GET_TARGET_PROPERTY( ShellSort_LOCATION ShellSort LOCATION)
SET( ShellSort_LOCATION \"${ShellSort_LOCATION}\")

#################################################################################
##	Very Slow Algorithms						       ##
#################################################################################

ADD_LIBRARY	( StoogeSort MODULE
			StoogeSort.cc
			stoogesort.h
		)
TARGET_LINK_LIBRARIES	( StoogeSort SortBase )
ADD_TEST	( NAME stooge_sort_test
		  COMMAND sortbench ${BAD_ALGO_TEST_SIZE} 1 $<TARGET_FILE:StoogeSort>
		)
GET_TARGET_PROPERTY( StoogeSort_LOCATION StoogeSort LOCATION)
SET( StoogeSort_LOCATION \"${StoogeSort_LOCATION}\")

CONFIGURE_FILE( config.in.h config.h)

IF (USE_QT)
	ADD_SUBDIRECTORY( gui/)
ENDIF (USE_QT)
