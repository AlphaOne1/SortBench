// vim: ts=8:sw=8:cindent
/********************************************************************************
*										*
*  Copyright (c) 2007-2010, Alexander Adam					*
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

/*! \file sortbase.h
 * In dieser Datei sind die Basisklasse fuer die Sortieralgorithmen und einige
 * kleine Helfer zum Laden dieser Klasse aus einer dynamischen Bibliothek
 * vorhanden.
 */

#ifndef __SORTBASE_H__
#define __SORTBASE_H__

#include <ostream>
#include <vector>

#ifdef _MSC_VER
	#ifdef SortBase_EXPORTS
		#define SORTBASE_API __declspec(dllexport)
	#else
		#define SORTBASE_API __declspec(dllimport)
	#endif
	#define EXPORT_API __declspec(dllexport)
#else
	#define SORTBASE_API
	#define EXPORT_API
#endif

namespace bench
{
	typedef	int			ele_t;	//!< Typ eines Feldelementes
	typedef std::vector< ele_t>	feld_t;	//!< Typ des Feldes
#ifdef _MSC_VER
	template class SORTBASE_API std::vector< ele_t>;
						//!< damit DLLs binaerkompatibel werden
#endif
	
	/*!
	 * Der Caster wird dazu benutzt, um Typen zu konvertieren. In diesem
	 * Fall gibt der Compiler eine Warnung aus, wenn ein Symbol einfach
	 * als Funktion interpretiert wird. Der Weg ueber den Caster unterbindet
	 * dies.
	 */
	union Caster
	{
		void*	obj_in;			//!< Datenzeiger
		void	(*fn_out)	(void);	//!< Funktionszeiger
	};

	/*!
	 * Basisklasse fuer die Sortieralgorithmen.
	 */
	class SORTBASE_API SortBase
	{
		public: //! Theoretische Geschwindigkeitseinstufung des Algorithmus
			enum SpeedGrade
			{
				VERY_SLOW	= 1,	//!< schlechter als O(n^2)
				SLOW		= 2,	//!< O(n^2)
				MEDIUM		= 3,	//!< original O(n^2), verbessert
				FAST		= 4,	//!< O(n log n)
				UNDEFINED	= 0 	//!< unbekanntes Laufzeitverhalten
			};
					SortBase	();
			virtual 	~SortBase	();

			virtual void	pre		( const bench::feld_t&);// Vorarbeiten
			virtual void	sort		() = 0;		//!< eigentliches Sortieren
			virtual void	post		();		// Nacharbeiten
				bool	test		();		// Test auf Korrektheit

			virtual	enum SpeedGrade
					speedGrade	() = 0;		//!< Geschwindigkeit
			virtual const char*
					name		() = 0;		//!< Namensausgabe


				void	output		( std::ostream&);// Feld ausgeben
		protected:
			feld_t	feld;					//!< zu sortierendes Feld
	};

	/*
	 * ABI der Module
	 */

	typedef	class SortBase*		(*create_t)	();			//!< Prototyp fuer Modulkonstruktion
	typedef	void			(*destroy_t)	( class SortBase*);	//!< Prototyp fuer Moduldestruktion
}

#endif /*__SORTBASE_H__*/
