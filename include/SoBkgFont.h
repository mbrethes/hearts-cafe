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
	\brief    Module charg� de la gestion des donn�es de polices � chasse fixe de 8 sur 8 pixels.

	 Singleton

	 Ce module renferme une police de caract�res, qui fonctionne avec le module 
	 \a SoBkg . Une police est faite d'un ensemble d'indices pointant vers des
	 caract�res de 8 sur 8 pixels. Ceux-si sont stock� dans un \a SoTileSet partag�.
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
// [fr] D�finition de types
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
  \brief    Structure de la police de caract�res.

  Une instance de \a SoBkgFont repr�sente un adressage des caract�res ASCII vers des
  indices de caract�res dans un TileSet. Notez qu'il est possible d'utiliser ce syst�me
  aussi bien pour des caract�res de 16 couleurs que de 256 couleurs. Cela permet d'utiliser
  le m�me adressage avec les deux modes -- cependant il faut v�rifier si les indices
  sont bien valides dans les deux jeux de caract�res.

  Tous les membres sont priv�s. Utilisez les m�thodes pour y acc�der.

  \todo  Cr�er une extension dont la taille pourrait varier (uniquement la largeur, ou bien la largeur et la hauteur).
*/

typedef struct
{
	u16     m_FirstChar;	//!< [en] \internal	First valid character in the font  
                                //!< [fr] \internal     Premier caract�re valide dans la police
	u16		m_NumChars;		//!< [en] \internal	Number of valid characters in the font
                                                //!< [fr] \internal     Nombre de caract�res valides dans la police
	u16*	m_CharMap;		//!< [en] \internal	character remapping data
                                        //!< [fr] \internal     donn�es de r�adressage des caract�res
} SoBkgFont;


// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] M�thodes publiques;
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
