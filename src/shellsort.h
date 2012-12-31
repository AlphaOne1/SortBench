// vim: ts=8:sw=8:cindent
/********************************************************************************
*										*
*  Copyright (c) 2008-2012, Alexander Adam					*
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

#ifndef __SHELLSORT_H__
#define __SHELLSORT_H__

#include <cstdlib>
#include "sortbase.h"

namespace shellsort
{
	class ShellSort : public bench::SortBase
	{
		public:		ShellSort		();
				~ShellSort		();

			void	pre			( const bench::feld_t&);
			void	sort			();

			enum bench::SortBase::SpeedGrade
				speedGrade	();
			const char*
				name		();

		protected:
			void	insert			( const bench::ele_t, const bench::feld_t::size_type, size_t);
			void	generate_sub_indices	( bench::feld_t::size_type);

			std::vector< bench::feld_t::size_type>	sub_indices;
			static const char			m_sort_name[];

			typedef std::vector< bench::feld_t::size_type>::size_type sub_ind_t;
	};
}

#endif // __SHELLSORT_H__
