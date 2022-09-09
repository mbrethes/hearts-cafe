// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoBkg.h
	\author		Mark T. Price, Jaap Suter
	\date		July 30 2002
	\ingroup	SoBkg

	See the \a SoBkg module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions d'utilisation et de distribution, veuillez consulter la notice
        de copyright dans SoLicense.txt

	\file		SoBkg.h
	\author		Mark T. Price, Jaap Suter
	\date		30 Juillet 2002
	\ingroup	SoBkg

	Voyez le module \a SoBkg pour plus d'informations.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_BKG_H
#define SO_BKG_H

#ifdef __cplusplus
	extern "C" {
#endif

// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoBkg SoBkg
	\brief	  Background specific functions

	Singleton

	This file handles everthing that has to do with a specific background instance. This
	module works together with the \a SoBkgManager, \a SoBkgMemManager and \a SoBkgMap
	modules.

	\todo Add support for screen sizes other than 256x256 pixels

	\todo Change to not do demand load for tiles that are not visible due to windowing.

	\todo Add support for mode 1, 2 screens

*/ 
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoBkg SoBkg
	\brief    Fonctions sp�cifiques aux arri�re-plans

	Singleton

	Ce fichier g�re tout ce qui touche une instance donn�e d'arri�re-plan. Ce module
	fonctionne en collaboration avec \a SoBkgManager, \a SoBkgMemManager et \a SoBkgMap.

	\todo Supporter des tailles d'�cran diff�rentes de 256x256 pixels
	\todo Changer pour ne pas demander le chargement des tiles qui ne sont pas visibles � cause du syst�me de fen�trage.
	\todo Supporter les �crans en mode 1 et 2
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------

#include "SoSystem.h"
#include "SoBkgMap.h"
#include "SoBkgFont.h"

// --------------------------------------------------------------------------------------
// [en] Defines
// [fr] D�finitions
// --------------------------------------------------------------------------------------

//! [en] The number of valid backgrounds
//! [fr] Le nombre de fonds d'�cran valides
#define SO_BKG_MAX_NUM_BACKGROUNDS  4

//! [en] Invalid background index used in SoBkgMap to disassociate from any backgrounds
//! [fr] Index de fond invalide utilis� dans SoBkgMap pour dissocier d'un quelconque fond existant
#define SO_BKG_NONE 0xffff

// [en] Background option bits
// [fr] bits d'option des fonds
#define SO_BKG_PRIORITY_0         0x0000		//!< [en] screen priority 0 (highest) 
	                                                //!< [fr] Priorit� d'�cran 0 (maximale)
#define SO_BKG_PRIORITY_1         0x0001		//!< [en] screen priority 1           
	                                                //!< [fr] Priorit� d'�cran 1
#define SO_BKG_PRIORITY_2         0x0002		//!< [en] screen priority 2           
	                                                //!< [fr] Priorit� d'�cran 2
#define SO_BKG_PRIORITY_3         0x0003		//!< [en] screen priority 3 (lowest)  
	                                                //!< [fr] Priorit� d'�cran 3 (minimale)

#define SO_BKG_CHARBASE(n)        (((n)&0x3)<<2)	//!< [en] starting tile offset in VRAM (n*16384) 
	                                                //!< [fr] offset du premier caract�re dans la VRAM (n*16384)

#define SO_BKG_MOSAIC_DISABLE     0x0000		//!< [en] mosaic mode disabled
	                                                //!< [fr] mode mosaique d�sactiv�
#define SO_BKG_MOSAIC_ENABLE      0x0040		//!< [en] mosaic mode enabled
	                                                //!< [fr] mode mosaique activ�

#define SO_BKG_CLRMODE_MASK       0x0080
#define SO_BKG_CLRMODE_16         0x0000		//!< [en] tile color mode (16 color)
                                                 	//!< [fr] mode de couleur des caract�res (16 couleurs)
#define SO_BKG_CLRMODE_256        0x0080		//!< [en] tile color mode (256 color)
	                                                //!< [fr] mode de couleur des caract�res (256 couleurs)

#define SO_BKG_SCRBASE_MASK       0x1f00
#define SO_BKG_SCRBASE(n)         (((n)&0x1f)<<8)	//!< [en] screen offset in VRAM (n*2048)
	                                                //!< [fr] offset de l'�cran dans la VRAM (n*2048)

#define SO_BKG_SIZE_MASK          0xc000
#define SO_BKG_TEXTSIZE_256x256   0x0000		//!< [en] text screen size 256x256 pixels (32x32 tiles)
	                                                //!< [fr] taille de l'�cran mode caract�re 256x256 pixels (32x32 caract�res)
#define SO_BKG_TEXTSIZE_512x256   0x4000		//!< [en] text screen size 512x256 pixels (64x32 tiles)
	                                                //!< [fr] taille de l'�cran mode caract�re 512x256 pixels (64x32 caract�res)
#define SO_BKG_TEXTSIZE_256x512   0x8000		//!< [en] text screen size 256x512 pixels (32x64 tiles)
	                                                //!< [fr] taille de l'�cran mode caract�re 256x512 pixels (32x64 caract�res)
#define SO_BKG_TEXTSIZE_512x512   0xc000		//!< [en] text screen size 512x512 pixels (64x64 tiles)
	                                                //!< [fr] taille de l'�cran mode caract�re 512x512 pixels (64x64 caract�res)

#define SO_BKG_ROTSIZE_128x128    0x0000		//!< [en] rot/scale screen size 128x128 pixels (16x16 tiles)
	                                                //!< [fr] taille de l'�cran mode rotation/zoom 128x128 pixels (16x16 caract�res)
#define SO_BKG_ROTSIZE_256x256    0x4000		//!< [en] rot/scale screen size 256x256 pixels (32x32 tiles)
                                                        //!< [fr] taille de l'�cran mode rotation/zoom 256x256 pixels (32x32 caract�res)
#define SO_BKG_ROTSIZE_512x512    0x8000		//!< [en] rot/scale screen size 512x512 pixels (64x64 tiles)
                                                        //!< [fr] taille de l'�cran mode rotation/zoom 512x512 pixels (64x64 caract�res)   
#define SO_BKG_ROTSIZE 1024x1024  0xc000		//!< [en] rot/scale screen size 1024x1024 pixels (128x128 tiles)
                                                        //!< [fr] taille de l'�cran mode rotation/zoom 1024x1024 pixels (128x128 caract�res)  

// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] M�thodes publiques;
// --------------------------------------------------------------------------------------

void SoBkgSetup(u32 a_Index, u32 a_Options);
void SoBkgEnable(u32 a_Index, bool a_Enable);

void SoBkgSetMosaicEnable( u32 a_Index, bool a_Enable );
void SoBkgSetPriority(u32 a_Index, u32 a_Priority);

void SoBkgSetOffset(u16 a_Index, u16 a_XPos, u16 a_YPos);

u16 *SoBkgGetData(u32 a_Index);

void SoBkgWrite(u16 a_Index, u16 a_XIndex, u16 a_YIndex, u16 a_Len, u16 *a_buffer);
void SoBkgWriteV(u16 a_Index, u16 a_XIndex, u16 a_YIndex, u16 a_Len, u16 *a_buffer);
void SoBkgWriteBlock(u16 a_Index, u16 a_XIndex, u16 a_YIndex, u16 a_Width, u16 a_Height, u16 a_Pitch,
					 u16 *a_buffer);

void SoBkgWriteIndirect(u16 a_Index, u16 a_XIndex, u16 a_YIndex, u16 a_Len, u16 *a_buffer);
void SoBkgWriteVIndirect(u16 a_Index, u16 a_XIndex, u16 a_YIndex, u16 a_Len, u16 *a_buffer);
void SoBkgWriteBlockIndirect(u16 a_Index, u16 a_XIndex, u16 a_YIndex, u16 a_Width, u16 a_Height,
							 u16 a_Pitch, u16 *a_buffer);

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SO_BKG_H
