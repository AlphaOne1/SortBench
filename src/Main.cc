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
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

#include "bench.h"

/*!
 * Hauptfunktion.
 *	\param	argc	Anzahl der uebergebenen Argumente (inklusive Programmname)
 *	\param	argv	Feld von Strings mit den Kommandozeilenargumenten
 *	\retval	EXIT_SUCCESS	wenn das Programm erfolgreich beendet wurde
 *	\retval EXIT_FAILURE	wenn das Programm nicht erfolgreich beendet wurde
 */
int main(int argc, char* argv[])
{
	class bench::Bench*	myBench;
	long			anz;
	long			seed;
	bool			found_bad = false;

	if (argc < 4)
	{
		std::cerr << "Usage: " << argv[ 0] << " <#elements> <seed> <module list>" << std::endl;
		return EXIT_FAILURE;
	}

	anz	= std::atoi( argv[ 1]);
	seed	= std::atoi( argv[ 2]);

	if (seed == 0)
		seed = (long)std::time( 0);

	if (anz <= 0)
	{
		std::cerr << "Invalid number of elements for sorting given!" << std::endl;
		return EXIT_FAILURE;
	}

	myBench = new class bench::Bench( anz, seed);
	myBench->init( 0);		//erstmal ungeordnet machen

	std::cout	<< std::setw( 22)	<< std::left	<< "module name"
			<< std::setw( 7)	<< std::right	<< "order"
			<< std::setw( 15)	<< "time in us" << std::endl;

	for (int i = 3; i < argc; i++)
	{
		myBench->loadmod( argv[ i]);

		long int zeit = myBench->test();

		if (myBench->badSorter())
		{
			found_bad = true;
		}

		std::cout	<< std::setw( 22)	<< std::left << myBench->getAktModName()
				<< std::setw( 7)	<< std::right<< myBench->getOrdnung()
				<< std::setw( 15)	<< zeit	<< std::endl;

		myBench->unloadmod();
	}

	delete myBench;

	if (found_bad)
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}
