// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		Socrates.h
	\author		Jaap Suter
	\date		March 7 2002
	\ingroup	Socrates

	See the \a Socrates module for more information. This file also contains some 
	information on the SGADE documentation in general, and some information
	on the philosophy and codestyle the SGADE uses.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions de distribution et d'utilisation, voyez la notice de copyright
	dans SoLicense.txt

	\file		Socrates.h
	\author		Jaap Suter
	\date		7 Mars 2002
	\ingroup	Socrates

	Voyez le module \a Socrates pour plus d'informations. Ce fichier contient également
	des informations sur la documentation de SGADE en général, et quelques informations
	sur la philosophie et le style de codage utilisé dans SGADE.
*/
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
/* [en]
	Scroll down to see the code this file contains. Cause first this file contains some
	general SGADE information. Sadly this text contains some HTML tags to incorporate
	it into the SGADE online documentation. Just try to ignore these, or read this text
	in the online version (where these tags actually improve readability).
*/
// ---------------------------------------------------------------------------------------
/* [fr]
       Faites défiler vers le bas pour voir le code que contient ce fichier, car ce fichier
       contient des informations générales sur SGADE. Malheureusement ces informations sont
       au format HTML pour pouvoir être incorporées à la documentation online de SGADE.
       Si vous ne pouvez lire ce fichier simplement, consultez la version en ligne (ou la
       lisibilité est meilleure).
*/
// ---------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
/*! [en]
	\mainpage The SGADE Documentation

	<CENTER>
		<B>Version 1.01</B> This text comes from the \a Socrates.h file.
	</CENTER>
		
	<B> Introduction to the Documentation </B>

	The documentation for the SGADE is divided into several parts. You are now reading the 
	largest section. It contains a complete reference to all code, and some background 
	information on the SGADE development philosophy and codestyle. Other information can 
	be found in the FAQ and the the tutorials. These can be found on the 
	<A HREF = "http://www.suddenpresence.com/sgade/">SGADE</A> website. 	
	
	Before you start using the SGADE I strongly suggest reading all information below. After
	that I would browse this reference for a bit, and start trying some tutorials.

	<B> Philosophy </B>

	I believe in object and component oriented programming. However, unlike some people,
	I also believe that one can use any coding paradigm in any language. I don't need C++ or 
	Java to use OOP, and I could do functional programming in assembly. Some languages might be
	better suited for some paradigms, but some languages are also better suited for some 
	platforms. This is the reason I chose C over C++ for Gameboy Advance development.

	I can see the merits in using C++ for a GBA project, but only for advanced management 
	systems. If, for example, I had to write a strategy game for the GBA, I would probably use
	C++ constructs to manage units and resources. But for Socrates, C gave me all I ever needed.
	Object oriented programming without the performance drawbacks of C++.
	
	If anyone wants to discuss this with me, and wants to tell me C++ can be just as fast, I'd
	love a discussion. But not until you've read Scott Meyer's books: Effective C++ and More 
	Effective C++.

	So, I would be using C. How then is OOP reflected in my C coding? Two things are 
	important here. This pointers and singletons. 
	
	This pointers are used whenever a function acts upon an object. In C++ all methods belonging 
	to a class receive an implicit (hidden) this pointer. Whenever you invoke a method on a class
	like this:
		
	\code 
		object.Method();
	\endcode

	What C++ actually does is this:

	\code 
		Method( &object );
	\endcode

	So all we have to do to emulate an object oriented class-method-like system is provide the
	this pointer ourselves. What better than using a short example. Take a look at the following
	C++ code.

	\code
		// Define the class
		class SoClass
		{
			// Attributes;
			int m_Attribute;

			// Methods;
			void Method1( void );
			void Method2( int a_Argument );
			int  Method3( void );
		}

		// Declare an instance;
		SoClass object

  		// Use the class
		object.Method1();
		object.Method2( 10 );
		int i = object.Method3();
	
	\endcode

	This would be written in C (the SGADE) as follows:

	\code
	
		// Define the structure
		typedef struct 
		{
			// Attributes;
			int attribute;
		} SoClass;

		// Define the methods;
		void SoClassMethod1( SoClass* a_This );
		void SoClassMethod2( SoClass* a_This, int a_Argument );
		int  SoClassMethod3( SoClass* a_This );

		// Declare an instance;
		SoClass object

  		// Use the class
		SoClassMethod1( &object );
		SoClassMethod2( &object, 10 );
		int i = SoClassMethod3( &object );

	\endcode

	Once you realize there is actually no difference between the above C++ and C code, nothing 
	stops you from doing OOP in C. It is true that the often called 'true' OOP concepts like 
	polymorphism and inheritance require more complicated constructs, but most of it can be 
	solved using clever casting and function pointers.

	What about singletons then? Well, targeting the Gameboy Advance, it turns out that a lot of 
	classes are often instantiated only once. A good example is an interrupt manager or a mode 4
	renderer. All methods belonging to such an object will always receive the same this pointer. 
	This would be nonsense ofcourse, and therefore we treat these objects as singletons. In 
	the SGADE a singleton is a group of global functions without this pointers. But we treat 
	those as methods belonging to and acting upon a single object and not as seperate functions.
	Consider the following functions:

	\code
		void SoMode4RendererEnable( void );
		void SoMode4RendererFlip( void );
		void SoMode4RendererClear( void );
			....
			
	\endcode

	All of these functions act upon a global fictional object called SoMode4Renderer. There is
	no SoMode4Renderer type, but the object is there. You will never see it, but just 
	remember that whenever you use a singleton. 

	C, as opposed to C++, has no build in information hiding facilities. Every attribute of a 
	structure is public (for the compiler). However, you should always treat all members of 
	every structure as  private. Use the supplied methods to act upon these structures. 
	
	There is a single exception to this. The \a SoVector3 and SoVector2 structures (because of 
	their simplicity) have public members. Every other structure has only private members. These
	are marked as 'For Internal Use Only'. Treat them that way.
	
	<B> Code Style </B>

	I use a fairly strict coding style. Uniform and consistent coding improves readability.
	I use the following rules for coding.

		- Basic datatypes are:
			- \a bool
			- \a u32
			- \a s32
			- \a u16
			- \a s16
			- \a u8
			- \a s8
			- \a char

		- Global variables start with \a g_

		- Static variables start with \a s_
		- Members of structures start with \a m_
		- Function arguments start with \a a_
		- Local variables start with a lowercase letter

		- Each new word within an identifier starts with an uppercase letter
		
		- Functions start with an uppercase letter.
		- Structures start with an uppercase letter.
		
		- Structures and functions are prefixed with \a So.
		- Functions belonging to a structure (methods) are prefixed with the structure name.

		- The opening curly bracket is always below the previous line.
		- The opening function bracket is always directly after the functionname.
		- An opening bracket is always followed by a space, and a closing bracket is 
		  always prefixed by a space.

		- Each function, non-local variable, and structure has a Doxygen-compatible description.
		  Scroll down for more information on Doxygen source documentation.

	The following piece of code gives some examples. Note that the large blocks of comments
	are normally done by using the / * and * / (without the spaces) comment style, but I can't 
	use these here cause this code example is embedded in a comment (yes this HTML is generated
	from a source file, see the next section on Doxygen for more information).

	\code

		// A global variable.
		u32 g_GlobalVariable;

		// A static variable.
		static u32 s_StaticVariable;

		// --------------------------------------------------------------------------
		//
		//	\brief	A global function.
		//	\param	a_Argument1			First argument of the function
		//	\param	a_Argument2			First argument of the function
		//	
		//	\return  The first argument added to the second argument.
		//	
		//	This function does blah blah blah
		//	          blah blah blah
		//					blah blah blah
		//	
		// --------------------------------------------------------------------------
		u32 SoGlobalFunction( u32 a_Argument1, u32 a_Argument2 )
		{
			// A local variable.
			u32	localVariable;

			// Do the calculation
			localVariable = a_Argument1 + a_Argument2;

			// Done;
			return localVariable;
		}
		// --------------------------------------------------------------------------
	
		// --------------------------------------------------------------------------
		//
		//	\brief This structure represents blah blah;
		//
		//	This structure can be used to do blah blah blah blah...
		//
		// --------------------------------------------------------------------------
		typedef struct
		{
			u32 m_MemberAttribute1;		// Attribute that is for blah....
			u32 m_MemberAttribute2;		// Attribute that is for bleh...
		
		} SoSomeStructure
		// --------------------------------------------------------------------------

		// --------------------------------------------------------------------------
		// 
		//	\brief	Method belonging to the SoSomeStructure class
		//	
		//	\param	a_This	This pointer
		//
		//	This function does blah blah blah blah...
		//
		// --------------------------------------------------------------------------
		void SoSomeStructureMethod( SoSomeStructure* a_This )
		{
			// Acces the member of the given this pointer.
			a_This->m_MemberAttribute = 10;
		}
		// --------------------------------------------------------------------------

	\endcode

	Just look at the above example and some of the SGADE code and you'll soon see the 
	consistency and particular coding practices I use to improve development.
	
	<B> On Doxygen Source Commenting </B>

	Doxygen is a tool that extracts comments from source code and creates documentation
	in HTML, Latex, or other formats. The very words you are reading now (if you are reading 
	this documentation in HTML format) have been extraced by Doxygen.

	More information on Doxygen can be found on its website 
	at <A HREF = "http://www.doxygen.org">http://www.doxygen.org</A> I'll give some short tips
	and advice that might help when you start browsing the SGADE sourcecode.

	Doxygen parses the sourcecode and uses the source surrounding comments to get information
	about this code. You can add certain tags to the comments to give Doxygen information about 
	what you mean with the code following the comments. 
	
	A Doxygen compatible source comment can be given in the following ways:

	- / *!	and a closing * / (without the space in between the *s and the /s) for a compound
			comment block, referring to the source after the block.
	- //!	For a single line Doxygen comment referring to the source after the comment.
	- //!<	For a single line Doxygen comment referring to the source before the comment.

	Inside a comment the following tags are used as special commands. Each tag is prefixed by 
	a \ (backslash).

	- \a a			- This means the single following word after the tag is a special word and 
					  needs special casing. 
	
	- \a file		- This tells Doxygen you want a file documented.
	
	- \a defgroup	- To define a group of functionality (a module).
	- \a ingroup	- To tell Doxygen this belongs to a certain group.
	
	- \a brief		- This gives a short one-line description on the following structure 
					  or function. As opposed to the more detailed description.
	
	- \a param 		- To give information on a function parameter.
	- \a return		- To give information on a function return value.
	- \a retval		- To give information on a function output parameter.
	
	- \a internal	- To specify something as 'For Internal Use Only'.
	
	There might be some more tags in the source I have forgotten here. But most of the time
	these will explain themselves.

	<B> Where to from here </B>

	Now that you have read something about the philosophy and coding style of the SGADE you know
	what to expect when using the SGADE. I suggest you start by browsing this reference, 
	especially the \a modules section at the top of this page. After that, browse through some 
	of the code and try some tutorials.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \mainpage La Documentation de SGADE

	<CENTER>
	       <B>Version 1.01</B> Ce texte est tiré du fichier \a Socrates.h .
	</CENTER>

	<B> Introduction à la documentation </B>

	la documentation de SGADE est divisée en plusieurs parties. Vous êtes en train de lire la
	section la plus large. Elle contient une référence complète de l'intégralité du code, ainsi
	que des informations sur la philosophie de développement et le style de codage employé pour
	SGADE. D'autres informations peuvent être trouvées sur les FAQ et dans les tutoriaux.
	Ceux-ci peuvent être trouvés sur le site internet de 
	<A HREF = "http://www.suddenpresence.com/sgade/">SGADE</A>.

	Avant de commencer à utiliser SGADE, Je vous recommande de lire les informations ci-dessous.
	Après cela, vous pourriez naviguer dans cette documentation et essayer quelques tutoriaux.

	<B> Philosophie </B>

	Je crois dans la programmation orientée objet. Cependant, et contrairement à certains, je
	crois aussi que l'on peut utiliser n'importe quelle méthode de programmation dans n'importe
	quel langage. Je n'ai pas besoin du C++ ou de Java pour faire de la POO, et je pourrais
	faire de la programmation structurée en assembleur. Certains langages seront probablement
	plus adaptés pour certains paradigmes, mais d'autres sont également plus adaptés à certaines
	plates-formes. C'est pour cela que j'ai choisi le C, plutôt que le C++, pour le développement
	sur Game Boy Advance.

	Je vois l'intérêt d'utiliser le C++ dans un projet GBA, mais uniquement pour des systèmes
	de gestion avancés. Si par exemple, je devais écrire un jeu de stratégie pour GBA,
	j'utiliserais probablement des objets C++ pour gérer les unités et les ressources. Mais pour
	Socrates, le C est amplement suffisant : programmation orientée objet sans les pertes de
	performances du C++.

	Si quelqu'un veut discuter avec moi sur ce point, et me dire que le C++ peut être aussi
	rapide, je serais ravi de pouvoir dialoguer. Mais pas avant que vous ayez lu ces bouquins
	de Scott Meyer : "Effective C++" et "More Effective C++" !

	Je vais donc utiliser le C. Comment donc la POO se reflète-t-elle dans mon code ? Deux choses
	sont importantes ici : les pointeurs "this" et les singletons.

	Les pointeurs "this" sont utilisés dès qu'une fonction agit sur un objet. En C++, toutes les
	méthodes appartenant à une classe reçoivent un pointeur "this" implicite (caché). Quand vous
	invoquez une méthode sur une classe comme ceci :

	\code 
		objet.Methode();
	\endcode

	Ce que fait en fait C++ est en fait ceci :

	\code 
		Methode( &objet );
	\endcode

	Tout ce que nous avons donc à faire pour émuler un système orienté-objet est de fournir le
	pointeur "this" nous-mêmes. Quoi de mieux que de prendre un petit exemple ? Etudiez le code
	C++ suivant.

	\code
		// Définition de la classe
		class SoClass
		{
			// Attributs;
			int m_Attribut;

			// Methodes;
			void Methode1( void );
			void Methode2( int a_Argument );
			int  Methode3( void );
		}

		// Déclarer une instance
		SoClass objet

  		// Utiliser la classe:
		objet.Methode1();
		objet.Methode2( 10 );
		int i = objet.Methode3();
	
	\endcode

	Ce même code s'écrirait en C (SGADE) comme suit :

	\code
	
		// Définition de la structure
		typedef struct 
		{
			// Attributs;
			int attribut;
		} SoClass;

		// Définition des méthodes
		void SoClassMethode1( SoClass* a_This );
		void SoClassMethode2( SoClass* a_This, int a_Argument );
		int  SoClassMethode3( SoClass* a_This );

		// Déclaration d'une instance
		SoClass objet

  		// Et utilisation de la classe
		SoClassMethode1( &objet );
		SoClassMethode2( &objet, 10 );
		int i = SoClassMethode3( &objet );

	\endcode

	Une fois compris le fait qu'il n'y a aucune différence entre les codes C++ Et C ci-dessus,
	rien ne vous empèche de faire de la programmation orientée objet en C. Il est vrai que ce
	que l'on appelle souvent les "vrais" concepts de POO comme le polymorphisme et l'héritage
	requièrent des constructions plus complexes, mais la quasi-totalité peut être réalisée à
	l'aide de subtils transtypages et de pointeurs de fonctions.

	Que dire alors des singletons ? Eh bien, si on considère le Game Boy Advance, il se trouve
	qu'un certain nombre de classes ne sont instanciées qu'une seule fois. Parmi les exemples,
	on trouvera un gestionnaire d'interruptions ou un moteur de rendu en mode 4. Toutes les
	méthodes apparenant à ces objets recevront toujours le même pointeur "this". Ce serait bien
	entendu absurde, et par conséquent nous traitons ces objets comme des singletons. Dans
	SGADE un singleton est un groupe de fonctions globales sans pointeur "this". Mais nous
	traitons ces fonctions comme des méthodes appartenant et agissant sur un objet unique, et non
	comme des fonctions séparées. Considérez les fonctions suivantes :

	\code
		void SoMode4RendererEnable( void );
		void SoMode4RendererFlip( void );
		void SoMode4RendererClear( void );
			....
			
	\endcode

	Toutes ces fonctions agissent sur un objet global fictif appelé SoMode4Renderer. Il n'existe
	pas de type SoMode4Renderer, mais l'objet est là. Vous ne le verrez jamais, mais n'oubliez pas
	ce principe lorsque vous utilisez un singleton.

	Contrairement au C++, le C n'a pas de système intégré de masquage d'information. Tout membre
	de structure est public (pour le compilateur). Cependant, VOUS devriez toujours traiter tous
	les membres de chaque tructure comme privés, et utiliser les méthodes fournies pour agir sur
	ces structures.

	Il y a une seule exception à cela. Les structures \a SoVector3 et SoVector2 ont des données
	publiques (vu leur simplicité). Toute autre structure a des données privées. Celles-ci sont
	indiquées comme "pour usage interne seulement". Traitez-les comme telles.

	<B> Style de codage </B>

	J'utilise un style de codage assez strict. Un style uniforme et cohérent améliore la lisibilité.
	J'utilise les règles suivantes pour coder :

	- Les types de données de base sont :
			- \a bool
			- \a u32
			- \a s32
			- \a u16
			- \a s16
			- \a u8
			- \a s8
			- \a char
	
	- Les noms de variables globales commencent par un \a g_

	- Les noms de variables statiques commencent par un  \a s_
	- Les noms de membres de structures commencent par un \a m_
	- Les noms d'arguments de fonctions commencent par un \a a_
	- Les variables locales commencent par une lettre minuscule

	- Chaque nouveau mot dans un identificateur commence avec une lettre majuscule

	- Les noms de fonctions commencent avec une lettre majuscule
	- Les noms de structures commencent avec une lettre majuscule

	- Les noms de structures et de fonctions commencent par un \a So.
	- Les fonctions apparenant à des structures (méthodes) sont préfixées du nom de la structure.

	- L'accolade ouvrante est toujours en dessous de la ligne précédente.
	- La parenthèse de fonction ouvrante est toujours juste après le nom de fonction.
	- Une parenthèse ouvrante est toujours suivie d'un espace, et la parenthèse fermanet est
	  toujours précédée d'un espace.
       
	- Chaque fonction, variable non locale et structure a une description compatible avec Doxygen.
	  Voyez plus loin pour des informations sur le système Doxygen.

       Le code suivant donne quelques exemples. Notez que les grands blocs de commentaires sont généralement
       faits en utilisant / * et * / ; mais je ne peux pas les utiliser ici car cet exemple de code est
       utilisé dans un commentaire (cet HTML est généré depuis un fichier source, voir la section suivante
       sur Doxygen pour plus d'informations).

       \code

		// Une variable globale
		u32 g_GlobalVariable;

		// Une variable statique
		static u32 s_StaticVariable;

		// --------------------------------------------------------------------------
		//
		//	\brief	Une fonction globale
		//	\param	a_Argument1			Premier argument de la fonction
		//	\param	a_Argument2			Second argument de la fonction
		//	
		//	\return  La somme du premier et du second argument
		//	
		//	Cette fonction fait bla bla bla
		//	          bla bla bla
		//					bla bla bla
		//	
		// --------------------------------------------------------------------------
		u32 SoGlobalFunction( u32 a_Argument1, u32 a_Argument2 )
		{
			// Une variable locale
			u32	localVariable;

			// Calcul !
			localVariable = a_Argument1 + a_Argument2;

			// Fini !
			return localVariable;
		}
		// --------------------------------------------------------------------------
	
		// --------------------------------------------------------------------------
		//
		//	\brief Cette structure représente bla bla bla
		//
		//	Cette structure peut être utilisée pour bla bla bla...
		//
		// --------------------------------------------------------------------------
		typedef struct
		{
			u32 m_MemberAttribute1;		// Cet attribut est pour bla...
			u32 m_MemberAttribute2;		// Cet attribut est pour bla...
		
		} SoSomeStructure
		// --------------------------------------------------------------------------

		// --------------------------------------------------------------------------
		// 
		//	\brief	Méthode appartenant à la classe SoSomeStructure
		//	
		//	\param	a_This	Pointeur "this"
		//
		//
		//      Cette fonction fait ceci-cela...
		//
		// --------------------------------------------------------------------------
		void SoSomeStructureMethod( SoSomeStructure* a_This )
		{
			// Accès au membre du pointeur "this" donné
			a_This->m_MemberAttribute = 10;
		}
		// --------------------------------------------------------------------------

	\endcode

	Regardez l'exemple ci-dessus et une partie du code de SGADE et vous comprendrez bientôt
	que la cohérence des pratiques de codage particulières que j'utilise permettent d'améliorer
	le développement.

	<B> A propos du système de commentaire de source Doxygen </B>

	Doxygen est un outil qui extrait les commentaires du code source et qui crée une 
	documentation en HTML, Latex, ou dans d'autres formats. Les mots qui vous lisez à présent
	(si vous lisez cette documentation en HTML) ont été extraits par Doxygen.

	Vous trouverez plus d'informations sur Doxygen sur leur site à l'adresse
	<A HREF = "http://www.doxygen.org">http://www.doxygen.org</A> (N.D.T. : C'est en anglais).
	Je vais vous donner quelques astuces et informations qui vous aideront quand vous
	commencerez à parcourir le code source de SGADE.

	Doxygen analyse le code source et utilise les commentaires qui l'entourent pour récupérer des
	informations sur ce code. Vous pouvez ajouter certaines étiquettes aux commentaires pour
	indiquer à Doxygen l'utilité du code qui suit le commentaire.

	Un commentaire compatible avec Doxygen peut être écrit de différentes manières :

	- / *! et un * / fermant (sans l'espace entre les * et les /) pour un bloc de grande taille,
	  se référant au source situé après le bloc.
	- //! pour un commentaire Doxygen sur une simple ligne, qui se réfère au source situé après
	  le commentaire.
	- //! pour un commentaire Doxygen sur une simple ligne, qui se réfère au source situé avant
	  le commentaire.

	Dans un commentaire, les étiquettes suivantes sont utilisées comme commandes spéciales. Chaque
	étiquette est préfixées avec un \ (antislash).

	- \a a        - signifie que le mot suivant cette étiquet et spécial et doit être agencé différemment.
	- \a file     - cela dit à Doxygen que l'on veut un qu'un fichier soit documenté.
	- \a defgroup - pour définir un groupe de fonctionnaliés (un module).
	- \a ingroup  - pour indiquer à Doxygen que ceci appartient à un certain groupe.
	- \a brief    - Ceci donne une courte description, sur une ligne, de la structure ou fonction
	                qui suit, à l'opposé de la fonction retournée.
        - \a param    - Donne de l'information sur un paramètre de fonctions.
        - \a return   - Donne de l'information sur la valeur de retour d'une fonction.
	- \a retval   - Donne de l'information sur le paramètre renvoyé par une fontion.
	- \a internal - pour spécifier que quelque chose est "uniquement à usage interne".

	Il se peut que vous trouviez des étiquettes dans le source que j'aurais oubliées. Mais la plupart
	du temps, elles sont simples à comprendre.

	<B> Et maintenant, que faire ? </B>

	A présent que vous avez lu ce document concernant la philosophie et le style de codage de SGADE,
	vous savez à quoi vous attendre en utilisant cette bibliothèque. Je vous recommande de commencer
	par parcourir cette référence, particulièrement la section \a modules en haut de page. Après cela,
	parcourez une partie du code et essayez quelques tutoriaux.
*/
// --------------------------------------------------------------------------------------

#ifndef SOCRATES_H
#define SOCRATES_H

// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup Socrates Socrates
	\brief	  Socrates header that includes all other headers

	Singleton

*/ 
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup Socrates Socrates
	\brief    L'en-tête de Socrates, qui inclut tous les autres en-têtes.

	Singleton
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------
#include "SoAssembly.h"
#include "SoBkg.h"
#include "SoBkgFont.h"
#include "SoBkgManager.h"
#include "SoBkgMemManager.h"
#include "SoBkgManager.h"
#include "SoCamera.h"
#include "SoDebug.h"
#include "SoDisplay.h"
#include "SoDMA.h"
#include "SoEffects.h"
#include "SoFlashMem.h"
#include "SoFont.h"
#include "SoIntManager.h"
#include "SoKeys.h"
#include "SoMath.h"
#include "SoMatrix.h"
#include "SoMemManager.h"
#include "SoMesh.h"
#include "SoMode4PolygonRasterizer.h"
#include "SoMode4Renderer.h"
#include "SoMultiPlayer.h"
#include "SoPalette.h"
#include "SoPolygon.h"
#include "SoSound.h"
#include "SoSprite.h"
#include "SoSpriteManager.h"
#include "SoSpriteMemManager.h"
#include "SoSpriteAnimation.h"
#include "SoSystem.h"
#include "SoTables.h"
#include "SoImage.h"
#include "SoTileSet.h"
#include "SoTimer.h"
#include "SoTransform.h"
#include "SoVector.h"
#include "SoWindow.h"

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------


//! @}

#endif




