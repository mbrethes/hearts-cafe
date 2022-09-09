// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoBkgFont.h
	\author		Mark T. Price
	\date		Jun 16 2002
	\ingroup	SoBkgFont

	See the \a SoBkgFont module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
        Pour les conditions de distribution et d'utilisation, consultez la notice de
	copyright dans SoLicense.txt

	\file		SoBkgFont.h
	\author		Mark T. Price
	\date		16 Juin 2002
	\ingroup	SoBkgFont

	Voyez le module \a SoBkgFont pour plus d'informations.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_BKG_FONT_H
#define SO_BKG_FONT_H

#ifdef __cplusplus
	extern "C" {
#endif

// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoBkgFont SoBkgFont
	\brief	  Module for handling 8 by 8 pixel fixed-width font data

	Singleton

	This module encapsulates a tile based font.  It works together with the \a SoBkg
	module.  A font is made up of a set of indices to 8 by 8 pixel characters.  The
	actual characters are stored in a shared \a SoTileSet.

	\todo  actually implement this module

	\todo  Merge with \a SoFont module

*/ 
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoBkgFont SoBkgFont
	\brief    Module chargé de la gestion des données de polices à chasse fixe de 8 sur 8 pixels.

	 Singleton

	 Ce module renferme une police de caractères, qui fonctionne avec le module 
	 \a SoBkg . Une police est faite d'un ensemble d'indices pointant vers des
	 caractères de 8 sur 8 pixels. Ceux-si sont stocké dans un \a SoTileSet partagé.
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------

#include "SoSystem.h"


// --------------------------------------------------------------------------------------
// [en] Typedefs
// [fr] Définition de types
// --------------------------------------------------------------------------------------

//! [en]
//! \brief	Background font structure
//!
//! A single \a SoBkgFont instance represents a mapping from ASCII characters to tile
//! indices in a TileSet.  Note that there is no requirement that the tiles be either
//! 16 or 256 color.  This allows the same font mapping to be used with both 16 and
//! 256 color tile sets -- though to do this care must be taken to ensure that the font
//! indices are valid in both tile sets.
//!
//! All the members are private. Use the methods instead.
//!
//! \todo	Create a variable size extension to this (width only or width/height)
//!
/*! [fr]
  \brief    Structure de la police de caractères.

  Une instance de \a SoBkgFont représente un adressage des caractères ASCII vers des
  indices de caractères dans un TileSet. Notez qu'il est possible d'utiliser ce système
  aussi bien pour des caractères de 16 couleurs que de 256 couleurs. Cela permet d'utiliser
  le même adressage avec les deux modes -- cependant il faut vérifier si les indices
  sont bien valides dans les deux jeux de caractères.

  Tous les membres sont privés. Utilisez les méthodes pour y accéder.

  \todo  Créer une extension dont la taille pourrait varier (uniquement la largeur, ou bien la largeur et la hauteur).
*/

typedef struct
{
	u16     m_FirstChar;	//!< [en] \internal	First valid character in the font  
                                //!< [fr] \internal     Premier caractère valide dans la police
	u16		m_NumChars;		//!< [en] \internal	Number of valid characters in the font
                                                //!< [fr] \internal     Nombre de caractères valides dans la police
	u16*	m_CharMap;		//!< [en] \internal	character remapping data
                                        //!< [fr] \internal     données de réadressage des caractères
} SoBkgFont;


// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] Méthodes publiques;
// --------------------------------------------------------------------------------------

//#define SoBkgFontGetFirstChar(a_This) (a_This->m_FirstChar)
//#define SoBkgFontGetNumChars(a_This)  (a_This->m_NumChars)
//#define SoBkgFontGetCharMap(a_This)   (a_This->m_CharMap)

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SO_BKG_FONT_H
