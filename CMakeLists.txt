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

PROJECT (SortBench)

CMAKE_MINIMUM_REQUIRED ( VERSION 3.0 )

FIND_PACKAGE( Qt4 COMPONENTS QtGui)
FIND_PACKAGE( Gettext)

IF (QT_FOUND)
	INCLUDE( ${QT_USE_FILE})
	SET( USE_QT TRUE CACHE BOOL "Toggle Qt usage")
ENDIF (QT_FOUND)

IF (GETTEXT_FOUND)
	SET( USE_GETTEXT TRUE CACHE BOOL "Toggle gettext usage")
ENDIF (GETTEXT_FOUND)

SET( CPACK_PACKAGE_VERSION_MAJOR "1")
SET( CPACK_PACKAGE_VERSION_MINOR "2")
SET( CPACK_PACKAGE_VERSION_PATCH "2")

SET( CPACK_SOURCE_GENERATOR "TBZ2")
SET( CPACK_SOURCE_IGNORE_FILES "/.*build/"
				".git/")
SET( CPACK_SOURCE_PACKAGE_FILE_NAME
"sortbench-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}_src")

INCLUDE( CPack)
ENABLE_TESTING()

ADD_SUBDIRECTORY( src/)
