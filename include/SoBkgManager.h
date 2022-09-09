// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoBkgManager.h
	\author		Jaap Suter
	\date		Feb 5 2002
	\ingroup	SoBkgManager

	See the \a SoBkgManager module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions d'utilisation et de distribution, veuillez consulter la notice
	de copyright dans le fichier SoLicense.txt

	\file		SoBkgManager.h
	\author		Jaap Suter
	\date		5 Février 2002
	\ingroup	SoBkgManager

	Voyez le module \a SoBkgManager pour plus d'informations.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_BKG_MANAGER_H
#define SO_BKG_MANAGER_H

#ifdef __cplusplus
	extern "C" {
#endif

// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoBkgManager SoBkgManager
	\brief	  Manages all backgrounds.

	Singleton

	This file handles everthing that has to do with backgrounds. This manager works
	together with the \a SoBkg module. This manager contains
	all background stuff not belonging to a particular \a SoBkg instance.

*/ 
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoBkgManager SoBkgManager
	\brieg    Gère tous les arrière-plans.

	Singleton

	Ce fichier gère tout ce qui touche aux arrière-plans. Ce système de gestion fonctionne
	avec le module \a SoBkg. Il contient toutes les fonctions d'arrière-plan qui
	n'appartiennent pas à une instance particulière de \a SoBkg.
*/
//! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------

#include "SoSystem.h"


// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] Méthodes publiques;
// --------------------------------------------------------------------------------------

void SoBkgManagerSetMosaic( u32 a_HorizontalSize, u32 a_VerticalSize );

// [en] deprecated functions
// [fr] Fonctions obsolètes
#define SoBackgroundManagerSetBackgroundEnable  SO_DEPRECATED_FUNCTION(SoBackgroundManagerSetBackgroundEnable, use_SoBkgEnable)
#define SoBackgroundManagerSetMosaic            SO_DEPRECATED_FUNCTION(SoBackgroundManagerSetMosaic, use_SoBkgManagerSetMosaic)
#define SoBackgroundManagerSetMosaicEnable      SO_DEPRECATED_FUNCTION(SoBackgroundManagerSetMosaicEnable, use_SoBkgSetMosaicEnable)


// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SO_BKG_MANAGER_H
