// --------------------------------------------------------------------------------------
/*! [en]
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoBkgMap.h
	\author		Mark T. Price
	\date		July 30 2002
	\ingroup	SoBkgMap

	See the \a SoBkgMap module for more information.
*/
// --------------------------------------------------------------------------------------
/*! [fr]
        Copyright (C) 2002 par les auteurs de SGADE
	Pour les condititons d'utilisation et de distribution, voyez la notice de copyright
	dans SoLicense.txt

	\file		SoBkgMap.h
	\author		Mark T. Price
	\date		30 Juillet 2002
	\ingroup	SoBkgMap

	Voyez le module \a SoBkgMap pour plus d'informations.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_BKG_MAP_H
#define SO_BKG_MAP_H

#ifdef __cplusplus
	extern "C" {
#endif

// --------------------------------------------------------------------------------------
/*! [en]
	\defgroup SoBkgMap SoBkgMap
	\brief	  Background map handling specific functions

	Singleton

	This module encapsulates a tile map used to define a Background.  It works
	together with the \a SoBkg module.

	Here is the fastest set-up code to clear and re-load a map on a background.  Changing
	the order of the SetBackground/SetScroll/SetBackground calls or eliminating the first
	SetBackground call will	result in additional work being done.

	\code
		SoBkgMapDisable(iBkg);						// turn off BKG (to avoid nasty artifacts)
		SoBkgMapSetBackground(pMap, SO_BKG_NONE);	// disassociate background
		SoBkgMapSetScroll(pMap, xpos, ypos);		// pre-load scroll position
		SoBkgMapSetBackground(pMap, iBkg);			// load screen & tiles
		SoBkgMapEnable(iBkg, iBkg);					// turn on BKG
	\endcode

	\todo Add high-level background support functions (demand-loaded scrolling of very large
	      map on BKG)

*/
// --------------------------------------------------------------------------------------
/*! [fr]
        \defgroup SoBkgMap SoBkgMap
	\brief    Fonctions sp�cifiques � la gestion des cartes d'arri�re-plan.

	Singleton

	Ce module encapsule une carte (tableau d'adresses) de caract�res utilis�e pour
	d�finir un arri�re-plan. Il fonctionne avec le module \a SoBkg.

	Voici le code le plus rapide pour effacer et recharger une carte sur un
	arri�re-plan. Changer l'ordre des appels de SetBackground/SetScroll/SetBackground
	ou �liminer le premier appel � Setbackground utilisera plus de ressources.
	
	\code
		SoBkgMapDisable(iBkg);						// d�sactiver l'arri�re-plan (pour �viter des probl�mes de hardware)
		SoBkgMapSetBackground(pMap, SO_BKG_NONE);	// d�sassocier l'arri�re-plan
		SoBkgMapSetScroll(pMap, xpos, ypos);		// Pr�charger la position de d�calage de la carte (scrolling)
		SoBkgMapSetBackground(pMap, iBkg);			// Charger la carte et les caract�res
		SoBkgMapEnable(iBkg, iBkg);					// activer l'arri�re-plan
	\endcode

	\todo Ajouter des fonctions de gestion haut niveau (beaucoup de demandes pour un
	      scrolling d'une grande carte sur un arri�re-plan).
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

//#define SO_BKG_MAP_MODE_RAW     0x0001	//!< [en] flag - raw mode map
//                   	                        //!< [fr] drapeau - carte en mode brut
//#define SO_BKG_MAP_MODE_DYNAMIC 0x0000  //!< [en] flag - dynamic mode map
//                                        //!< [fr] drapeau - carte dynamique

// --------------------------------------------------------------------------------------
// [en] Typedefs
// [fr] D�finition de types
// --------------------------------------------------------------------------------------

//! [en] \brief	Background map structure
//!
//! A single \a SoBkgMap instance represents a virtual playfield for a single BKG layer.
//! The map may reside in ROM if no data will be written to it (such as for a static
//! scrolling background) or in RAM if it must be updated.
//!
//! All the members are private. Use the methods instead.
//!
/*! [fr] 
        \brief Structure de carte d'arri�re-plan
         
        Une simple instance de \a SoBkgMap repr�sente une ar�ne virtuelle pour une couche donn�e
        d'arri�re-plan. Cette carte peut r�sider en ROM si aucune donn�e ne doit y �tre �crite
	(c'est le cas pour un arri�re-plan d�roulant statique) ou en RAM s'il faut la mettre �
        jour.

	Tous les membres de la structure sont priv�s. Utilisez les m�thodes pour y acc�der.
*/

typedef struct
{
	bool    m_16Colors;			//!< [en] \internal	True if the map is 16 colors, false if 256 colors
                                                //!< [fr] \internal     True si la carte est en 16 couleurs, false sinon. 
//	u16     m_Mode;				//!< [en] \internal  operation mode
//                                              //!< [fr] \internal  mode d'op�ration
//	u16     m_Bkg;				//!< [en] \internal	Background associated with this map
//                                              //!< [fr] \internal     arri�re-plan associ� � la carte
	u16     m_PalBank;			//!< [en] \internal	The bank of colors to use for this map if in
								//!<            16 color mode (0 - 15)
                                                //!< [fr] \internal     La banque de couleurs � utiliser pour cette carte
                                                                //!<            pour le mode 16 couleurs (0-15)
	u16     m_SizeX;			//!< [en] \internal  number of columns in map
                                                //!< [fr] \internal  nombre de colonnes dans la carte
	u16     m_SizeY;			//!< [en] \internal	number of rows in map
                                                //!< [fr] \internal     nombre de lignes dans la carte
	u16*    m_Data;				//!< [en] \internal	actual map data (tile indices)
                                                //!< [fr] \internal     donn�es de la carte (indices des caract�res)
//	const SoBkgFont *m_Font;	//!< [en] \internal	active font for this map
//                                      //!< [fr] \internal     police active pour cette carte
} SoBkgMap;

// --------------------------------------------------------------------------------------
// [en] Public methods;
// [fr] M�thodes publiques;
// --------------------------------------------------------------------------------------

// [en] the functions/macros below that are currently commented out will be moved here
// from SoBkg prior to the 1.01 stable release
// [fr] les fonctions et macros mises en commentaire ci-dessous seront mises ici
// � partir de SoBkg, avant la livraision de la version 1.01

//! [en] \brief	Tells you whether the tileset is 16 colors or 256 colors;
//!
//! \param	a_This This pointer
//! 
//! \return	True if 16 color tile, false if 256 color tile;
//!
/*! [fr]
        \brief Indique si le jeu de caract�res est en 16 ou en 256 couleurs;

	\param a_This Un pointeur sur SoBkgMap

	\return True si nous avons 16 couleurs, False sinon.
*/
#define SoBkgMapIs16Colors(a_This)     ((a_This)->m_16Colors)

//#define SoBkgMapIsRaw(a_This)          ((a_This)->m_Mode & SO_BKG_MAP_MODE_RAW)
//#define SoBkgMapGetBackground(a_This)  ((a_This)->m_Bkg)


//! [en] \brief	Tells what 16-color bank of colors to use for this map
//!
//! \param a_This	This pointer
//!
//! \returns 0 to 15 palette bank for 16-color tiles
//!
/*! [fr]
        \brief Indique quelle banque de 16 couleurs est utilis�e pour la carte

	\param a_This   Un pointeur sur un SoBkgMap

	\returns Si le jeu de caract�res est en 16 couleurs, un indice compris 
	         entre 0 et 15 correspondant au num�ro de palette.
*/
#define SoBkgMapGetPaletteBank(a_This) ((a_This)->m_PalBank)

//! [en] \brief	Retrieves the width of the map
//!
//! \param a_This	this pointer
//!
//! \returns the number of columns in the map
//!
/*! [fr]
        \brief Renvoie la largeur de la carte (coordonn�e x)

	\param a_This Un pointeur sur un SoBkgMap

	\returns le nombre de colonnes dans la carte
*/
#define SoBkgMapGetNumCols(a_This)     ((a_This)->m_SizeX)

//! [en] \brief	Retrieves the height of the map
//!
//! \param a_This	this pointer
//!
//! \returns the number of rows in the map
//!
/*! [fr]
        \brief Retourne la hauteur de la carte (coordonn�e y)

	\param a_This    Un pointeur sur un SoBkgMap
	
	\returns le nombre de lignes dans la carte
*/
#define SoBkgMapGetNumRows(a_This)     ((a_This)->m_SizeY)

//! [en] \brief	Retrieves pointer to the map data
//!
//! \param a_This	this pointer
//!
//! \returns pointer to the upper left corner of the map
//!
/*! [fr]
        \brief Retourne un pointeur vers les donn�es de la carte

	\param a_This Un pointeur sur un SoBkgMap
	
	\returns un pointeur vers le coin sup�rieur gauche du contenu de la carte
*/
#define SoBkgMapGetData(a_This)        ((a_This)->m_Data)

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SO_BKG_MAP_H
