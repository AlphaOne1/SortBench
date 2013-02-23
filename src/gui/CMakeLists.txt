# vim: set ts=8 sw=8 autoindent smartindent: ####################################
#										#
#  Copyright (c) 2012-2013, Alexander Adam					#
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

SET( sortgui_SRCS
		main.cc
		SortBenchMain.cc
)

SET( sortgui_HDRS
		SortBenchMain.h
)

SET( sortgui_MOC_SRCS
		SortBenchMain.h
)

SET( sortgui_UIC_SRCS
		main.ui
)

OPTION( UPDATE_TRANSLATIONS "Update the translation source files (.ts). Be
careful as this also enable make to remove them alltogher on \"make clean\"")

QT4_WRAP_CPP( sortgui_MOCS ${sortgui_MOC_SRCS})
QT4_WRAP_UI( sortgui_UICS ${sortgui_UIC_SRCS})
IF (UPDATE_TRANSLATIONS)
	QT4_CREATE_TRANSLATION( sortgui_QMS ${CMAKE_CURRENT_SOURCE_DIR} translation.ts)
ELSE (UPDATE_TRANSLATIONS)
	QT4_ADD_TRANSLATION( sortgui_QMS translation.ts)
ENDIF (UPDATE_TRANSLATIONS)
QT4_ADD_RESOURCES( sortgui_RCS resources.qrc)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE( sortgui
		${sortgui_HDRS}
		${sortgui_MOCS}
		${sortgui_SRCS}
		${sortgui_UICS}
		${sortgui_RCS}
		${sortgui_QMS}
)

TARGET_LINK_LIBRARIES( sortgui
		${QT_LIBRARIES}
)
