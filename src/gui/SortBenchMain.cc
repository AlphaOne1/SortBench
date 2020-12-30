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

#include <QStandardItemModel>

#include "SortBenchMain.h"
#include "ui_main.h"

SortBenchMain::SortBenchMain( QWidget *parent) : QMainWindow( parent),
						 mUi( new Ui::MainWindow)
{
	mUi->setupUi( this);

	QStandardItemModel	*model	= new QStandardItemModel();
	QStandardItem		*root	= model->invisibleRootItem();
	QStandardItem		*item;

	QObject::connect( mUi->actionAbout_Qt, SIGNAL( triggered()), this, SIGNAL( aboutQtTriggered()));

	model->setHorizontalHeaderLabels( QStringList( (tr( "Algorithm,Time")).split(",")));

	QStandardItem *algo_class = new QStandardItem( tr("Fast"));
	root->appendRow( algo_class);

		item = new QStandardItem( QString("BinaryTreeSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("CountingSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("HeapSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("MergeSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("QuickSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("RadixSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("STLSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

	algo_class = new QStandardItem( tr("Medium"));
	root->appendRow( algo_class);

		item = new QStandardItem( QString("CombSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("InsertionSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

	algo_class = new QStandardItem( tr("Slow"));
	root->appendRow( algo_class);

		item = new QStandardItem( QString("BubbleSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("SelectionSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

		item = new QStandardItem( QString("ShellSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

	algo_class = new QStandardItem( tr("Very Slow"));
	root->appendRow( algo_class);

		item = new QStandardItem( QString("StoogeSort"));
		item->setCheckable( true);
		algo_class->appendRow( item);

	mUi->algorithmView->setModel( model);
}

SortBenchMain::~SortBenchMain()
{
	delete mUi;
}
