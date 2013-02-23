/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2007-2013, Alexander Adam					*
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

#include <cstdlib>
#include "binarytreesort.h"

using namespace binary_tree;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return static_cast< class bench::SortBase*>(new class BinTreeSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class BinTreeSort*>( x);
	}
}

const char BinTreeSort::m_sort_name[] = "BinaryTreeSort";

BinTreeSort::BinTreeSort()
{
	m_pos	= 0;
	m_root	= NULL;
}

BinTreeSort::~BinTreeSort()
{
	del_tree(m_root);
}

enum bench::SortBase::SpeedGrade BinTreeSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* BinTreeSort::name()
{
	return BinTreeSort::m_sort_name;
}

void BinTreeSort::sort()
{
	for (bench::feld_t::size_type i = 0; i < this->feld.size(); ++i)
	{
		insert( &m_root, feld[ i]);
	}
	dfs_run( m_root);
}

void BinTreeSort::post()
{}

void BinTreeSort::insert( struct tree_node** n, const bench::ele_t data)
{
	if (*n == NULL)
	{
		*n = new struct tree_node;
		(*n)->left	= NULL;
		(*n)->right	= NULL;
		(*n)->data	= data;
	}
	else
	{
		if (data < (*n)->data)
			insert( &((*n)->left), data);
		else
			insert( &((*n)->right), data);
	}
}

void BinTreeSort::dfs_run( const struct tree_node* n)
{
	if (n == NULL)
		return;
	else
	{
		dfs_run( n->left);
		feld[ m_pos++] = n->data;
		dfs_run( n->right);
	}
}

void BinTreeSort::del_tree( struct tree_node* n)
{
	if (n == NULL)
		return;
	else
	{
		del_tree(n->left);
		del_tree(n->right);
		delete n;
	}
}
