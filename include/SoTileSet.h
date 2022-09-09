// --------------------------------------------------------------------------------------
/*! 
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoTileSet.h
	\author		Jaap Suter, Mark T. Price
	\date		July 30 2001
	\ingroup	SoTileSet

	See the \a SoTileSet module for more information.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_TILESET_H
#define SO_TILESET_H

#ifdef __cplusplus
	extern "C" {
#endif


// --------------------------------------------------------------------------------------
/*! 
	\defgroup SoTileSet SoTileSet
	\brief	  Module for handling sets of 8 by 8 pixel tiles.

	A tile is an 8x8 square of palettized pixels. Either referring to a 
	16 color palette, or a 256 color palette.

	You can use the SoConverter tool to convert images to tilesets.

*/ //! @{
// --------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------------
#include "SoSystem.h"

// --------------------------------------------------------------------------------------
// Typedefs
// --------------------------------------------------------------------------------------

/*!
	\brief	Tileset structure. 

	A single \a SoTileSet instance represents a collection of 8 by 8 pixel squares.

	All the members are private. Use the methods instead.
*/
typedef struct
{	
	bool	m_16Colors;		//!< \internal	True if the tileset is 16 colors, false if 256 colors.
	u16		m_NumTiles;		//!< \internal	Number of tiles in the tileset.
	u8*		m_Data;			//!< \internal	Actual tileset data (palette indices).
} SoTileSet;

// --------------------------------------------------------------------------------------
// Public methods;
// --------------------------------------------------------------------------------------

u32	 SoTileSetGetSize(	   const SoTileSet* a_This );
u32  SoTileSetGetNumTiles( const SoTileSet* a_This );
bool SoTileSetIs16Colors(  const SoTileSet* a_This );
u16* SoTileSetGetData(	   const SoTileSet* a_This );

void SoTileSetBkgLoad(const SoTileSet* a_This, u32 a_CharBase, u32 a_BaseIdx);

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

