// --------------------------------------------------------------------------------------
/*! 
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoPalette.h
	\author		Jaap Suter
	\date		August 9 2001
	\ingroup	SoPalette

	See the \a SoPalette module for more information.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_PALETTE_H
#define SO_PALETTE_H

#ifdef __cplusplus
	extern "C" {
#endif


// --------------------------------------------------------------------------------------
/*! 
	\defgroup SoPalette SoPalette
	\brief	  All palette handling

	This module takes care of everything that has to do with palettes.	

	A palette is just an array of 15 bit BGR color values, each in a 16 bit word.
	So we're just using \a u16*'s for palettes.
	
	A palette contains either 16 or 256 colors. This information is not stored inside the 
	palette. Most of the time you know it when using it anyway. 
	
	Because a palette is already a pointer in itself, we can directly use the \a SoPalette
	object as a this pointer.
	
	You can use the SoPaletteConverter.exe tool in the /tools/ directory to convert Jasc 
	palettes to a Socrates compatible header file. Ready to be included in a socrates project.	
	
*/ //! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------------
#include "SoSystem.h"

// ------------------------------------------------------------------------------------
// Defines
// ------------------------------------------------------------------------------------

// Start of sprite palette;
#define SO_SPRITE_PALETTE			((u16*)0x5000200)			//!< Sprite palette

// Start of screen palette;			
#define SO_SCREEN_PALETTE			((u16*)0x5000000)			//!< Screen palette


// ------------------------------------------------------------------------------------
// Public methods;
// ------------------------------------------------------------------------------------
void SoPaletteSetColor( u16* a_This, u32 a_PalIndex, u32 a_16BitColor );

void SoPaletteSetBlack(		u16* a_This, bool a_256ColorPalette );
void SoPaletteSetGreyScale(	u16* a_This, bool a_256ColorPalette );
void SoPaletteSetRandom(	u16* a_This, bool a_256ColorPalette );
void SoPaletteSetPalette(	u16* a_This, const u16* a_Palette, bool a_256ColorPalette );

void SoPaletteFadeGreyScale( u16* a_This, u32 a_Fade, bool a_256ColorPalette );
void SoPaletteFadePalette(	 u16* a_This, const u16* a_Palette, u32 a_Fade, bool a_256ColorPalette );

void SoPaletteAddToPalette(			u16* a_This, u32 a_Red, u32 a_Green, u32 a_Blue, bool a_256ColorPalette );
void SoPaletteSubtractFromPalette(  u16* a_This, u32 a_Red, u32 a_Green, u32 a_Blue, bool a_256ColorPalette );

// --------------------------------------------------------------------------------------
// EOF;
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif


