// --------------------------------------------------------------------------------------
/*! [en] 
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoDebug.h
	\author		Matt Hattem, Jaap Suter, Mark T. Price
	\date		March 14 2001
	\ingroup	SoDebug

	See the \a SoDebug module for more information. 
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions d'utilisation et de distribution, consultez la notice de
	copyright dans SoLicense.txt

	file		SoDebug.h
	\author		Matt Hattem, Jaap Suter, Mark T. Price
	\date		14 Mars 2001
	\ingroup	SoDebug

	Voyez le module \a SoDebug pour plus d'informations.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_DEBUG_H
#define SO_DEBUG_H

#ifdef __cplusplus
	extern "C" {
#endif


// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoDebug SoDebug
	\brief	  All debug related functionality

	Singleton

	This module contains all stuff related to debugging, like debug-output, 
	assertions, etc.

*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoDebug SoDebug
	\brief Toutes les fonctionnalités liées au déboguage

	Singleton

	Ce module contient toutes les fonctionnalités liées au déboguage, comme les
	assertions, les sorties de déboguage, etc.
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes;
// [fr] Inclusions;
// --------------------------------------------------------------------------------------
#include "SoSystem.h"

// --------------------------------------------------------------------------------------
// [en] Defines;
// [fr] Définitions;
// --------------------------------------------------------------------------------------

/*! [en] 
	\brief Undefine this (comment it) if you are going to do a release build;
    
	When this is not defined then assertions are optimized away, as well as some 
	other stuff that is done. It's all magic :) hehe...

	However, you can always be sure that if something works in debug mode, it WILL work in 
	release mode too.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \brief Commentez la définition ci-dessous si vous projetez de compiler une version finale;

	Quand ceci n'est pas défini, les assertions sont retirées du code, ainsi que
	quelques autres choses qui sont réalisées. C'est automagique :-)

	Vous pouvez cependant être sûr que si quelque chose fonctionne en mode déboguage,
	cela fonctionnera aussi en mode "version finale".
*/
#define SO_DEBUG

/*! 
   [en]	\brief		Define that controls what system the debugprint should use.
   [fr] \brief          Des définitions qui controlent le système d'affichage des infos de déboguage.	
*/
// [en] Only one or zero of these macros may be defined at any time;
// [fr] Seule une ou zéro de ces macros doit être définie à n'importe quel moment.
// #define SO_DEBUG_RUNNING_ON_MAPPY
// #define SO_DEBUG_RUNNING_ON_MBV2
// #define SO_DEBUG_RUNNING_ON_BATGBA


// --------------------------------------------------------------------------------------
// [en] Macros
// [fr] Macros
// --------------------------------------------------------------------------------------

/*! [en]
	\brief Assertion macro.

	\param a_Assertion		Expression that results in a boolean value (true, false, 0 or non zero).
	\param a_Message		Message that is displayed when the assertion fails.    
	
	This macro can be used for assertions. When you are running a debug build and the given 
	assertion fails, it halts the program and displays the assertion, the message, the line 
	number, and the name of the file in which the assertion is located.

	In release builds (when SO_DEBUG is not defined) these assertions are removed
	by the preprocessor.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \brief Macro d'assertion.

	\param a_Assertion   Expression qui retourne une valeur booléenne (true, false, 0 ou non zéro).
	\param a_Message     Le message à afficher lorsque l'assertion échoue.

	Cette macro peut être utilisée pour générer des assertions. Lorsque vous exécutez un
	programme compilé en mode déboguage et que l'assertion donnée échoue, le programme
	stoppe et l'assertion est affichée comme suit : texte de l'assertion, numéro de ligne,
	nom du fichier où l'assertion se trouvait.

	Lorsque SO_DEBUG n'est pas défini, les assertions sont retirées du code par le préprocesseur.
*/
#ifdef SO_DEBUG
	#define	SO_ASSERT( a_Assertion, a_Message )		\
			SoDebugAssert( (a_Assertion),			\
							(a_Message),			\
							#a_Assertion,			\
							__FILE__,				\
							__LINE__ )				
#else
	#define SO_ASSERT( a_Assertion, a_Message )
#endif

/*! [en]
	\brief Prints debug messages;

	\param a_String Message you want to display;

	This macro routs the given string to a console depending 
	on the \a SO_DEBUG_RUNNING_ON_* defines.

	In release builds (when SO_DEBUG is not defined) these debug prints are removed
	by the preprocessor.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \brief Affiche des messages de déboguage;

	\param a_String Le message à afficher;

	Cette macro redirige la chaîne passée en paramètre vers la console, de manière à
	correspondre aux définitions \a SO_DEBUG_RUNNING_ON_*.

	Lorsque SO_DEBUG n'est pas défini, ces affichages de déboguage sont retirés par le
	préprocesseur.
*/
#ifdef SO_DEBUG
	#define	SO_DEBUG_PRINT( a_String )	SoDebugPrint( a_String )
#else
	#define	SO_DEBUG_PRINT( a_String )	
#endif

//! [en] \brief	generates a breakpoint (BATGBA only)
//!
//! \param	a_BreakNum	ID number of the breakpoint
//!
// --------------------------------------------------------------------------------------
/*! [fr]
  \brief Génère un point d'arrêt (seulement avec BATGBA)

  \param a_BreakNum          Le numéro d'identification du point d'arrêt.
*/
#ifdef SO_DEBUG_RUNNING_ON_BATGBA
#define SO_DEBUG_BREAK(a_BreakNum)			asm ("swi " #a_BreakNum " << 16 + 0x90");
#endif


/*! [en]
	\brief	Compile-time assertion.
	
	\param a_Assertion		Expression that results in a boolean value (true, false, 0 or non zero).
	\param a_Message		Message that is displayed when the assertion fails. This must be an identifier 
							not a string, due to the nature of this assertion (compile-time). So if you 
							want to say "Value 64 not allowed", then just use Value_64_not_allowed instead. And
							if you don't understand this, then you shouldn't be using compile time assertions.

	This is to check certain preconditions during the compile phase, like values of constants
	and their relations. If the assertion fails, you will get an error from the compiler, 
	telling you where the assertion occured. This error might look a bit weird, something like
	size of array .... is negative. But the array identifier will given an indication of 
	what happened. You can then go to the line of the error for a better explanation.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \brief Assertion de compilation.

	\param a_Assertion            Expression qui retourne une valeur booléenne.
	\param a_Message              Message affiché lorsque l'assertion échoue. Il doit s'agir d'un identificateur
                                          valide C, et non d'une chaine de caractères, vu la nature de l'assertion
					  (exécutée au moment de la compilation). Si vous voulez afficher par exemple
					  "La valeur 64 n'est pas autorisee", utilisez Valeur_64_Interdite à la place.
					  Si vous n'avez rien compris à ce paragraphe, n'utilisez pas d'assertions
					  de compilation.

       Ces assertions permettent de vérifier certaines préconditions lors de la phase de compilation,
       comme des valeurs de constantes ou leurs relations. Si l'assertion échoue, une erreur du compilateur
       s'affichera, en indiquant où l'assertion a échoué. Cette erreur peut paraître un peu étrange,
       quelque chose dans le style "size of array .... is negative". Mais le pointeur de tableau vous
       donnera une indication de ce qui s'est produit. Vous pouvez ensuite consultez la ligne d'erreur
       pour une meilleure explication.
*/
#define SO_COMPILE_TIME_ASSERT( a_Assertion, a_Message ) typedef char COMPILE_TIME_ASSERTION_FAILED_##a_Message[(a_Assertion) != 0 ? 1 : -1] 

/*! [en]
	\brief	Deprecated function declaration macro

	\param a_FunctionName	Name of the function that has been deprecated
	\param a_Message		Message to explain what to do instead (if anything)

	This macro gives a more friendly notification to a user of the SGADE library
	if they are attempting to use a function that is no longer supported.  It should
	make it much easier to track down the error than getting a link error, or the
	old method of providing a stub for the removed function that just asserts.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \brief Macro de déclaration de fonction obsolète

	\param a_FunctionName    Le nom de la fonction rendue obsolète
	\param a_Message         Le message expliquant ce qui doit être fait (si c'est le cas)

	Cette macro donne une notification plus agréable à un utilisateur de SGADE lorsque
	celui-ci essaie d'utiliser une fonction qui n'est plus supportée. Ceci est bien plus
	simple pour détecter les erreurs qu'obtenir une erreur à la phase d'édition de liens.
*/
#define SO_DEPRECATED_FUNCTION(a_FunctionName, a_Message) SO_COMPILE_TIME_ASSERT(0, a_FunctionName##_has_been_deprecated_##a_Message);


// --------------------------------------------------------------------------------------
// [en] Private functions;
// [fr] Fonctions privées;
// --------------------------------------------------------------------------------------

void SoDebugAssert(	bool a_Assertion, 
					char* a_Message, 
					char* a_Expression, 
					char* a_File, 
					u32 a_Line );

void SoDebugPrint(const char* a_Message);

// [en] helper functions
// [fr] fonctions auxiliaires
void ditoa(s32 num, char*buf, int len, int base);
char *dstrcpy(u8 *strdst, const u8 *strsrc);
char *dstrcpynum(u8 *strdst, s32 value, int base);
u16   dstrlen(u8 *str);
void SoDebugPrintIntValue(const char *a_Name, s32 a_Value, int base);


// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------


//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
