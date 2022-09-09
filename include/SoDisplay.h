// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoDisplay.h
	\author		Jaap Suter
	\date		Jan 1 2002	
	\ingroup	SoDisplay

	See the \a SoDisplay module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions de distribution et d'utilisation, consultez la notice de
	copyright dans SoLicense.txt

	\file		SoDisplay.h
	\author		Jaap Suter
	\date		1 Janvier 2002	
	\ingroup	SoDisplay

	Consultez le module \a SoDisplay pour plus d'informations.
*/

#ifndef SO_DISPLAY_H
#define SO_DISPLAY_H

#ifdef __cplusplus
	extern "C" {
#endif


// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoDisplay SoDisplay
	\brief	  All general display related stuff.

	Singleton

	This module contains and defines everything related to the display of the GBA. Very 
	specific stuff gets it's own module like \a SoMode4Renderer and \a SoMode4PolygonRasterizer
	but this module contains the most general stuff.
		
*/ 
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoDisplay SoDisplay
	\brief    L'ensemble des fonctions li�es � la gestion de l'affichage.

	Singleton

	Ce module contient et d�finit tout ce qui est li� � l'affichage du GBA. Il existe
	des modules sp�cifiques comme \a SoMode4Renderer et \a SoMode4PolygonRasterizer
	contenant des fonctions d�taill�es, mais ce module contient les choses les plus
	g�n�rales.
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------
#include "SoSystem.h"

// --------------------------------------------------------------------------------------
// [en] Defines
// [fr] D�finitions
// --------------------------------------------------------------------------------------

//! [en] GBA display control register, defined in the header cause it's used in multiple files.
//! [fr] Registre de contr�le de l'affichage du GBA, d�fini dans l'en-t�te car utilis� dans de multiples fichiers.
#define SO_REG_DISP_CNT				(*(volatile u16*)0x4000000)	

//! [en] GBA display statistics register, defined in the header cause it's used in multiple files.
//! [fr] Registre de statistiques d'affichage,  d�fini dans l'en-t�te car utilis� dans de multiples fichiers.
#define SO_REG_DISP_STAT			(*(volatile u16*)0x4000004)	

//! [en] GBA scanline counter register, defined in the header cause it's used in multiple files.
//! [fr] Registre de comptage de la ligne de balayage, d�fini dans l'en-t�te car utilis� dans de multiples fichiers.
#define SO_REG_SCANLINE_COUNT		(*(volatile u16*)0x4000006)	

//! [en] GBA display mosaic register, defined in the header cause it's used in multiple files.
//! \warning Write only register. Use the \a SO_REG_DISP_MOSAIC_RW register instead.
//! [fr] Registre d'affichage mosaique du GBA, d�fini dans l'en-t�te car utilis� dans de multiples fichiers.
//! \warning Ce registre est en �criture seule. Utilisez le registre \a So_REG_DISP_MOSAIC_RW � la place.
#define		SO_REG_DISP_MOSAIC_W 		(*(volatile u16*)0x400004C)	

//! [en] GBA display mosaic register backup, so we can both read and write;
//! \warning This register needs to be copied into SO_REG_DISP_MOSAIC_W to have any effect.
//! [fr] Copie du registre d'affichage mosaique du GBA, afin de pouvoir lire et �crire.
//! \warning Ce registre doit �tre copi� dans SO_REG_DISP_MOSAIC_W pour avoir un effet.
extern u16 SO_REG_DISP_MOSAIC_RW;

// [en] Screen dimensions;
// [fr] Dimensions de l'�cran:					
#define SO_SCREEN_WIDTH				240							//!< [en] Width of the GBA screen
	                                                                                                //!< [fr] Largeur de l'�cran du GBA
#define SO_SCREEN_HALF_WIDTH		(SO_SCREEN_WIDTH / 2)		//!< [en] Half of the GBA screen width
	                                                                //!< [fr] Demi-largeur de l'�cran du GBA.
#define SO_SCREEN_HEIGHT			160							//!< [en] Height of the GBA screen
	                                                                                                //!< [fr] Hauteur de l'�cran du GBA
#define SO_SCREEN_HALF_HEIGHT		(SO_SCREEN_HEIGHT / 2)		//!< [en] Half of the GBA screen height
	                                                                //!< [fr] Demi-hauteur de l'�cran du GBA

// [en] Colors
// [fr] Couleurs
#define SO_RED						(SO_5_BITS)						//!< [en] Pure red;
	                                                                                                        //!< [fr] Rouge pur;
#define SO_GREEN					(SO_5_BITS << 5)				//!< [en] Pure green;
	                                                                                                //!< [fr] Vert pur;
#define SO_BLUE						(SO_5_BITS << 10)				//!< [en] Pure blue;
	                                                                                                //!< [fr] Bleu pur;
#define SO_WHITE					(SO_RED | SO_GREEN | SO_BLUE)	//!< [en] Pure white;
	                                                                                //!< [fr] Blanc pur;
#define SO_BLACK					0								//!< [en] Pure black;
	                                                                                                                //!< [fr] Noir pur;
#define SO_YELLOW					(SO_RED | SO_GREEN)				//!< [en] Pure yellow;
	                                                                                                //!< [fr] Jaune pur;
#define SO_CYAN						(SO_BLUE | SO_GREEN)			//!< [en] Pure cyan;
	                                                                                        //!< [fr] Cyan pur;
#define SO_MAGENTA					(SO_RED | SO_BLUE)				//!< [en] Pure magenta (purple);
	                                                                                                //!< [fr] Magenta pur (violet);
#define SO_PURPLE					SO_MAGENTA					//!< [en] Pure purple (magenta);
	                                                                                                //!< [fr] Alias du pr�c�dent (vous aimez Deep Purple ?)

// --------------------------------------------------------------------------------------
// [en] Macros
// [fr] Macros
// --------------------------------------------------------------------------------------

#define SO_RGB( r, g, b )		(((b)<<10)+((g)<<5)+(r))	//!< [en] Converts three 5 bit values for RGB into one 16 bit RGB value.
	                                                                //!< [fr] Convertit 3 valeurs sur 5-bit pour du RGB en une valeur RGB 16-bit.
#define SO_RGB_GET_R( c )		(((c)&(31    ))    )		//!< [en] Extracts the 5 bit R value out of a 15 bit RGB value.
	                                                                //!< [fr] Extrait la valeur R sur 5 bit d'une valeur RGB 16-bit (15 actifs)
#define SO_RGB_GET_G( c )		(((c)&(31<< 5))>> 5)		//!< [en] Extracts the 5 bit G value out of a 15 bit RGB value.
	                                                                //!< [fr] Extrait la valeur G sur 5 bit d'une valeur RGB 16-bit (15 actifs)
#define SO_RGB_GET_B( c )		(((c)&(31<<10))>>10)		//!< [en] Extracts the 5 bit B value out of a 15 bit RGB value.
	                                                                //!< [fr] Extrait la valeur B sur 5 bit d'une valeur RGB 16-bit (15 actifs)

#define SO_SCREEN_HALF_WIDTH_MULTIPLY( y ) (((y)<<7)-((y)<<3))	//!< [en] Multiplies the given number by the half width (120) of the GBA screen;
	                                                        //!< [fr] Multiplie la valeur donn�e par la demi-largeur de l'�cran du GBA (120)

// --------------------------------------------------------------------------------------
// [en] Functions
// [fr] Fonctions
// --------------------------------------------------------------------------------------

void SoDisplayInitialize(		  void );

void SoDisplayEnable(u32 a_Enable);

void SoDisplaySetMode(u32 a_Mode);
u32  SoDisplayGetMode(void);

u32	 SoDisplayGetVCounter(		  void );

bool SoDisplayIsInVBlank(		  void );
bool SoDisplayIsInHBlank(		  void );

void SoDisplayWaitForVBlankStart( void );
void SoDisplayWaitForVBlankEnd(	  void );

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif
	
#endif
