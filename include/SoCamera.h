// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoCamera.h
	\author		Jaap Suter
	\date		Jun 26 2001
	\ingroup	SoCamera

	See the \a SoCamera module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les conditions d'utilisation et de distribution, voyez la notice de copyright
	dans SoLicense.txt

	\file		SoCamera.h
	\author		Jaap Suter
	\date		26 Juin 2001
	\ingroup	SoCamera

	Voyez le module \a SoCamera pour plus d'informations.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_CAMERA_H
#define SO_CAMERA_H

#ifdef __cplusplus
	extern "C" {
#endif

// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoCamera SoCamera
	\brief	  Camera for rendering 3D primitives

	This file contains the definitions of the camera
	class. Cameras are used to project and render 3 dimensional primitives
	onto the GBA screen.
	
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoCamera SoCamera
	\brief Caméra pour le rendu des primitives 3D

	Ce fichier contient les définitions de la classe Caméra. Les caméras sont utilisées
	pour projeter et créer le rendu de primitives tridimensionelles sur l'écran du GBA.
*/
//! @{
// --------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------
// [en] Includes
// [fr] Inclusions
// --------------------------------------------------------------------------------------
#include "SoVector.h"
#include "SoTransform.h"
#include "SoMatrix.h"
#include "SoMesh.h"
#include "SoPolygon.h"
#include "SoMath.h"
#include "SoDisplay.h"

// --------------------------------------------------------------------------------------
// [en] Typedefs
// [fr] Définition de types
// --------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------
/*! [en]
	\brief Used to render 3D stuff.

	Cameras are used to project and render 3 dimensional primitives
	onto the GBA screen.

	See the \a SoCamera module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \brief utilisé pour le rendu 3D.

	Les caméras sont utilisées pour projeter et créer le rendu des primitives tridimensionelles
	sur l'écran du GBA.

	Voyez le module \a SoCamera pour plus d'informations.
*/
// --------------------------------------------------------------------------------------
typedef struct
{
	SoTransform m_Transform;					//!< [en] \internal 
                                                                        //!< [fr] \internal

	SoVector3	m_LeftFrustumPlaneNormal;		//!< [en] \internal 
                                                                //!< [fr] \internal
	SoVector3	m_TopFrustumPlaneNormal;		//!< [en] \internal
                                                                //!< [fr] \internal 

	bool		m_ClipAgainstFarAndNearPlane;	//!< [en] \internal
                                                        //!< [fr] \internal 
	bool		m_ClipAgainstFrustumSidePlanes;	//!< [en] \internal
                                                        //!< [fr] \internal 

	s32			m_NearPlaneDistance;			//!< [en] \internal
                                                                        //!< [fr] \internal 
	s32			m_FarPlaneDistance;				//!< [en] \internal
                                                                                //!< [fr] \internal 
	s32			m_ProjectionPlaneDistance;		//!< [en] \internal
                                                                        //!< [fr] \internal 

} SoCamera;
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] Méthodes publiques;
// --------------------------------------------------------------------------------------
void SoCameraInitialize( SoCamera* a_This );

void SoCameraPitch(		 SoCamera* a_This, s32 a_Angle );
void SoCameraYaw(		 SoCamera* a_This, s32 a_Angle );
void SoCameraRoll(		 SoCamera* a_This, s32 a_Angle );

void SoCameraForward(	 SoCamera* a_This, sofixedpoint a_Amount );
void SoCameraRight(		 SoCamera* a_This, sofixedpoint a_Amount );
void SoCameraUp(		 SoCamera* a_This, sofixedpoint a_Amount );

void SoCameraSetPitch(	 SoCamera* a_This, s32 a_Angle );
void SoCameraSetYaw(	 SoCamera* a_This, s32 a_Angle );
void SoCameraSetRoll(	 SoCamera* a_This, s32 a_Angle );

void SoCameraSetTranslation( SoCamera* a_This, sofixedpoint a_X, sofixedpoint a_Y, sofixedpoint a_Z );

void SoCameraDrawMesh(	 SoCamera* a_This, SoMesh* a_Mesh );

void SoCameraSetFarAndNearPlaneClippingEnable( SoCamera* a_This, bool a_Enable );
void SoCameraSetFrustumSidePlanesClippingEnable( SoCamera* a_This, bool a_Enable );

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
