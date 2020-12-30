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

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR})

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
	IF (USE_INTL)
		TARGET_INCLUDE_DIRECTORIES( sortbench
						PRIVATE ${Intl_INCLUDE_DIRS}
					)
		TARGET_LINK_LIBRARIES	( sortbench
						SortBase
						dl
						${Intl_LIBRARIES}
					)
    ELSE(USE_INTL)
		TARGET_LINK_LIBRARIES	( sortbench
						SortBase
						dl
					)
	ENDIF(USE_INTL)
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

ADD_LIBRARY	( CombSort MODULE
			CombSort.cc
			combsort.h
		)
TARGET_LINK_LIBRARIES	( CombSort SortBase)
ADD_TEST	( NAME comb_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:CombSort>
		)

ADD_LIBRARY	( CountingSort MODULE
			CountingSort.cc
			countingsort.h
		)
TARGET_LINK_LIBRARIES	( CountingSort SortBase )
ADD_TEST	( NAME counting_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:CountingSort>
		)

ADD_LIBRARY	( HeapSort MODULE
			HeapSort.cc
			heapsort.h
		)
TARGET_LINK_LIBRARIES	( HeapSort SortBase )
ADD_TEST	( NAME heap_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:HeapSort>
		)

ADD_LIBRARY	( MergeSort MODULE
			MergeSort.cc
			mergesort.h
		)
TARGET_LINK_LIBRARIES	( MergeSort SortBase )
ADD_TEST	( NAME merge_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:MergeSort>
		)

ADD_LIBRARY	( QuickSort MODULE
			QuickSort.cc
			quicksort.h
		)
TARGET_LINK_LIBRARIES	( QuickSort SortBase )
ADD_TEST	( NAME quick_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:QuickSort>
		)

ADD_LIBRARY	( RadixSort MODULE
			RadixSort.cc
			radixsort.h
		)
TARGET_LINK_LIBRARIES	( RadixSort SortBase )
ADD_TEST	( NAME radix_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:RadixSort>
		)

ADD_LIBRARY	( STLSort MODULE
			STLSort.cc
			stlsort.h
		)
TARGET_LINK_LIBRARIES	( STLSort SortBase )
ADD_TEST	( NAME stl_sort_test
		  COMMAND sortbench ${FAST_ALGO_TEST_SIZE} 1 $<TARGET_FILE:STLSort>
		)

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

ADD_LIBRARY	( InsertionSort MODULE
			InsertionSort.cc
			insertionsort.h
		)
TARGET_LINK_LIBRARIES	( InsertionSort SortBase )
ADD_TEST	( NAME insertion_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:InsertionSort>
		)

ADD_LIBRARY	( MinMaxSort MODULE
			MinMaxSort.cc
			minmaxsort.h
		)
TARGET_LINK_LIBRARIES	( MinMaxSort SortBase )
ADD_TEST	( NAME minmax_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:MinMaxSort>
)

ADD_LIBRARY	( SelectionSort MODULE
			SelectionSort.cc
			selectionsort.h
		)
TARGET_LINK_LIBRARIES	( SelectionSort SortBase )
ADD_TEST	( NAME selection_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:SelectionSort>
		)

ADD_LIBRARY	( ShellSort MODULE
			ShellSort.cc
			shellsort.h
		)
TARGET_LINK_LIBRARIES	( ShellSort SortBase )
ADD_TEST	( NAME shell_sort_test
		  COMMAND sortbench ${SLOW_ALGO_TEST_SIZE} 1 $<TARGET_FILE:ShellSort>
		)

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

SET( Locale_LOCATION \"${CMAKE_CURRENT_BINARY_DIR}\")

CONFIGURE_FILE( config.in.h config.conf.h @ONLY)
FILE(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/config.h INPUT ${CMAKE_CURRENT_BINARY_DIR}/config.conf.h)

IF (USE_QT)
	ADD_SUBDIRECTORY( gui/)
ENDIF (USE_QT)
