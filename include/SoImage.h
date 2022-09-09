// --------------------------------------------------------------------------------------
/*! 
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoImage.h
	\author		Jaap Suter
	\date		June 20 2001	
	\ingroup	SoImage

	See the \a SoImage module for more information.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_TEXTURE_H
#define SO_TEXTURE_H

#ifdef __cplusplus
	extern "C" {
#endif


// --------------------------------------------------------------------------------------
/*! 
	\defgroup SoImage SoImage
	\brief	  For all image handling
	
	This module represents 8bit palettized and 16bit images

	You can use the \a SoConverter.exe tool to convert image data to 
	Socrates compatible header files, ready to be included in the project.

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
	\brief	Texture structure.
	
	This structure represents an image, and is used by \a SoMesh for example. All
	its members are private, and you should only use the \a SoImage methods to 
	acces these attributes.
*/
typedef struct
{
	u16		m_Width;		//!< \internal Width of the image;
	u16		m_Height;		//!< \internal Height of the image;
	
	bool    m_Palettized;   //!< \internal True if the image is palettized, false otherwise;
	
	u16*	m_Data;			//!< \internal Array of image data;
	
} SoImage;

// --------------------------------------------------------------------------------------
// Public methods;
// --------------------------------------------------------------------------------------
u32  SoImageGetWidth(     const SoImage* a_This );
u32  SoImageGetHeight(    const SoImage* a_This );
u16* SoImageGetData(	  const SoImage* a_This );
bool SoImageIsPalettized( const SoImage* a_This );


// --------------------------------------------------------------------------------------
// EOF;
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
