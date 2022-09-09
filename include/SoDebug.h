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
	\brief Toutes les fonctionnalit�s li�es au d�boguage

	Singleton

	Ce module contient toutes les fonctionnalit�s li�es au d�boguage, comme les
	assertions, les sorties de d�boguage, etc.
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
// [fr] D�finitions;
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
        \brief Commentez la d�finition ci-dessous si vous projetez de compiler une version finale;

	Quand ceci n'est pas d�fini, les assertions sont retir�es du code, ainsi que
	quelques autres choses qui sont r�alis�es. C'est automagique :-)

	Vous pouvez cependant �tre s�r que si quelque chose fonctionne en mode d�boguage,
	cela fonctionnera aussi en mode "version finale".
*/
#define SO_DEBUG

/*! 
   [en]	\brief		Define that controls what system the debugprint should use.
   [fr] \brief          Des d�finitions qui controlent le syst�me d'affichage des infos de d�boguage.	
*/
// [en] Only one or zero of these macros may be defined at any time;
// [fr] Seule une ou z�ro de ces macros doit �tre d�finie � n'importe quel moment.
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

	\param a_Assertion   Expression qui retourne une valeur bool�enne (true, false, 0 ou non z�ro).
	\param a_Message     Le message � afficher lorsque l'assertion �choue.

	Cette macro peut �tre utilis�e pour g�n�rer des assertions. Lorsque vous ex�cutez un
	programme compil� en mode d�boguage et que l'assertion donn�e �choue, le programme
	stoppe et l'assertion est affich�e comme suit : texte de l'assertion, num�ro de ligne,
	nom du fichier o� l'assertion se trouvait.

	Lorsque SO_DEBUG n'est pas d�fini, les assertions sont retir�es du code par le pr�processeur.
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
        \brief Affiche des messages de d�boguage;

	\param a_String Le message � afficher;

	Cette macro redirige la cha�ne pass�e en param�tre vers la console, de mani�re �
	correspondre aux d�finitions \a SO_DEBUG_RUNNING_ON_*.

	Lorsque SO_DEBUG n'est pas d�fini, ces affichages de d�boguage sont retir�s par le
	pr�processeur.
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
  \brief G�n�re un point d'arr�t (seulement avec BATGBA)

  \param a_BreakNum          Le num�ro d'identification du point d'arr�t.
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

	\param a_Assertion            Expression qui retourne une valeur bool�enne.
	\param a_Message              Message affich� lorsque l'assertion �choue. Il doit s'agir d'un identificateur
                                          valide C, et non d'une chaine de caract�res, vu la nature de l'assertion
					  (ex�cut�e au moment de la compilation). Si vous voulez afficher par exemple
					  "La valeur 64 n'est pas autorisee", utilisez Valeur_64_Interdite � la place.
					  Si vous n'avez rien compris � ce paragraphe, n'utilisez pas d'assertions
					  de compilation.

       Ces assertions permettent de v�rifier certaines pr�conditions lors de la phase de compilation,
       comme des valeurs de constantes ou leurs relations. Si l'assertion �choue, une erreur du compilateur
       s'affichera, en indiquant o� l'assertion a �chou�. Cette erreur peut para�tre un peu �trange,
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
        \brief Macro de d�claration de fonction obsol�te

	\param a_FunctionName    Le nom de la fonction rendue obsol�te
	\param a_Message         Le message expliquant ce qui doit �tre fait (si c'est le cas)

	Cette macro donne une notification plus agr�able � un utilisateur de SGADE lorsque
	celui-ci essaie d'utiliser une fonction qui n'est plus support�e. Ceci est bien plus
	simple pour d�tecter les erreurs qu'obtenir une erreur � la phase d'�dition de liens.
*/
#define SO_DEPRECATED_FUNCTION(a_FunctionName, a_Message) SO_COMPILE_TIME_ASSERT(0, a_FunctionName##_has_been_deprecated_##a_Message);


// --------------------------------------------------------------------------------------
// [en] Private functions;
// [fr] Fonctions priv�es;
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
