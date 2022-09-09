// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoBkgMemManager.h
	\author		Mark T. Price
	\date		July 30 2002
	\ingroup	SoBkgMemManager

	See the \a SoBkgMemManager module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions d'utilisation et de distribution, voyez la notice de copyright
	dans SoLicense.txt
	
	\file		SoBkgMemManager.h
	\author		Mark T. Price
	\date		30 Juillet 2002
	\ingroup	SoBkgMemManager

	Voyez le module \a SoBkgMemManager pour plus d'information.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_BKG_MEM_MANAGER_H
#define SO_BKG_MEM_MANAGER_H

#ifdef __cplusplus
	extern "C" {
#endif

// --------------------------------------------------------------------------------------
/*! [en] 
	\defgroup SoBkgMemManager SoBkgMemManager
	\brief	  Manages background memory.

	Singleton

	This module handles the character data for backgrounds. It loads data into the BKG
	VRAM area as needed by the \a SoBkg and \a SoBkgMap modules.
	So before you start using \a this module read about these other two modules too.

	This implementation is closely based on Rafael Baptista's GDC 2001 talk on GBA
	resource management	that was later posted on http://www.gamasutra.com
	Unfortunately the article was removed from the site due to legal reasons.

*/ 
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoBkgMemManager SoBkgMemManager
	\brief    Gère la mémoire des arrière-plans.

	Singleton

	Ce module gère les données de caractères pour les arrière-plans. Il charge les données
	dans la VRAM d'arrière-plan comme requis par les modules \a SoBkg et \a SoBkgMap.
	Nous vous conseillons de lire la documentation de ces deux autre modules avant
	d'utiliser celui-ci.

	Cette implémentation est basée sur l'article de Rafael Baptista, traitant de la gestion
	des ressources sur GBA. Cet article, posté un temps sur http://www.gamasutra.com , a
	depuis été retiré du site pour des raisons juridiques.
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------

#include "SoSystem.h"
#include "SoTileSet.h"

// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] Méthodes publiques;
// --------------------------------------------------------------------------------------

void SoBkgMemManagerPreInitialize(void);
void SoBkgMemManagerAllocTileSet(const SoTileSet* a_TileSet, u32 a_CharBase, u32 a_BaseIdx);
void SoBkgMemManagerAllocBkg(u32 a_Options);
void SoBkgMemManagerInitialize(void);

void SoBkgMemManagerSetTileSet(const SoTileSet *a_TileSet, u16 *a_TileMapBuffer);

u16  SoBkgMemManagerAllocTile(u32 a_TileIdx);
void SoBkgMemManagerFreeTile(u32 a_TileIdx);

u16  SoBkgMemManagerAllocTile16(u32 a_TileIdx);
void SoBkgMemManagerFreeTile16(u32 a_TileIdx);

/*
void SoBkgMemManagerFreeBkg(u32 a_Options);
void SoBkgMemManagerFreeTileSet(const SoTileSet* a_This, u32 a_CharBase, u32 a_BaseIdx);
*/

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SO_BKG_MEM_MANAGER_H
