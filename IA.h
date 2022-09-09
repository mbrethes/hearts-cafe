#ifndef __IA_HEADER__
#define __IA_HEADER__

/* Ce fichier contient les fonctions "d'intelligence artificielle"
   du jeu.
*/

#include "HeartsEngine.h"
#include <Socrates.h>

void definirStrategieInitiale(u8 joueur);

void redefinirStrategie(u8 joueur);

void donnerCartesIAAlea(u8 joueur, u8* buffer);

u8 jouerCarteIAAlea(u8 joueur);

void donnerCartesIABasic(u8 joueur, u8* buffer);

u8 jouerCarteIABasic(u8 joueur);

#endif
