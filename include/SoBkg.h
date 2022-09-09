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
	\brief    Fonctions spécifiques aux arrière-plans

	Singleton

	Ce fichier gère tout ce qui touche une instance donnée d'arrière-plan. Ce module
	fonctionne en collaboration avec \a SoBkgManager, \a SoBkgMemManager et \a SoBkgMap.

	\todo Supporter des tailles d'écran différentes de 256x256 pixels
	\todo Changer pour ne pas demander le chargement des tiles qui ne sont pas visibles à cause du système de fenétrage.
	\todo Supporter les écrans en mode 1 et 2
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
// [fr] Définitions
// --------------------------------------------------------------------------------------

//! [en] The number of valid backgrounds
//! [fr] Le nombre de fonds d'écran valides
#define SO_BKG_MAX_NUM_BACKGROUNDS  4

//! [en] Invalid background index used in SoBkgMap to disassociate from any backgrounds
//! [fr] Index de fond invalide utilisé dans SoBkgMap pour dissocier d'un quelconque fond existant
#define SO_BKG_NONE 0xffff

// [en] Background option bits
// [fr] bits d'option des fonds
#define SO_BKG_PRIORITY_0         0x0000		//!< [en] screen priority 0 (highest) 
	                                                //!< [fr] Priorité d'écran 0 (maximale)
#define SO_BKG_PRIORITY_1         0x0001		//!< [en] screen priority 1           
	                                                //!< [fr] Priorité d'écran 1
#define SO_BKG_PRIORITY_2         0x0002		//!< [en] screen priority 2           
	                                                //!< [fr] Priorité d'écran 2
#define SO_BKG_PRIORITY_3         0x0003		//!< [en] screen priority 3 (lowest)  
	                                                //!< [fr] Priorité d'écran 3 (minimale)

#define SO_BKG_CHARBASE(n)        (((n)&0x3)<<2)	//!< [en] starting tile offset in VRAM (n*16384) 
	                                                //!< [fr] offset du premier caractère dans la VRAM (n*16384)

#define SO_BKG_MOSAIC_DISABLE     0x0000		//!< [en] mosaic mode disabled
	                                                //!< [fr] mode mosaique désactivé
#define SO_BKG_MOSAIC_ENABLE      0x0040		//!< [en] mosaic mode enabled
	                                                //!< [fr] mode mosaique activé

#define SO_BKG_CLRMODE_MASK       0x0080
#define SO_BKG_CLRMODE_16         0x0000		//!< [en] tile color mode (16 color)
                                                 	//!< [fr] mode de couleur des caractères (16 couleurs)
#define SO_BKG_CLRMODE_256        0x0080		//!< [en] tile color mode (256 color)
	                                                //!< [fr] mode de couleur des caractères (256 couleurs)

#define SO_BKG_SCRBASE_MASK       0x1f00
#define SO_BKG_SCRBASE(n)         (((n)&0x1f)<<8)	//!< [en] screen offset in VRAM (n*2048)
	                                                //!< [fr] offset de l'écran dans la VRAM (n*2048)

#define SO_BKG_SIZE_MASK          0xc000
#define SO_BKG_TEXTSIZE_256x256   0x0000		//!< [en] text screen size 256x256 pixels (32x32 tiles)
	                                                //!< [fr] taille de l'écran mode caractère 256x256 pixels (32x32 caractères)
#define SO_BKG_TEXTSIZE_512x256   0x4000		//!< [en] text screen size 512x256 pixels (64x32 tiles)
	                                                //!< [fr] taille de l'écran mode caractère 512x256 pixels (64x32 caractères)
#define SO_BKG_TEXTSIZE_256x512   0x8000		//!< [en] text screen size 256x512 pixels (32x64 tiles)
	                                                //!< [fr] taille de l'écran mode caractère 256x512 pixels (32x64 caractères)
#define SO_BKG_TEXTSIZE_512x512   0xc000		//!< [en] text screen size 512x512 pixels (64x64 tiles)
	                                                //!< [fr] taille de l'écran mode caractère 512x512 pixels (64x64 caractères)

#define SO_BKG_ROTSIZE_128x128    0x0000		//!< [en] rot/scale screen size 128x128 pixels (16x16 tiles)
	                                                //!< [fr] taille de l'écran mode rotation/zoom 128x128 pixels (16x16 caractères)
#define SO_BKG_ROTSIZE_256x256    0x4000		//!< [en] rot/scale screen size 256x256 pixels (32x32 tiles)
                                                        //!< [fr] taille de l'écran mode rotation/zoom 256x256 pixels (32x32 caractères)
#define SO_BKG_ROTSIZE_512x512    0x8000		//!< [en] rot/scale screen size 512x512 pixels (64x64 tiles)
                                                        //!< [fr] taille de l'écran mode rotation/zoom 512x512 pixels (64x64 caractères)   
#define SO_BKG_ROTSIZE 1024x1024  0xc000		//!< [en] rot/scale screen size 1024x1024 pixels (128x128 tiles)
                                                        //!< [fr] taille de l'écran mode rotation/zoom 1024x1024 pixels (128x128 caractères)  

// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] Méthodes publiques;
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
