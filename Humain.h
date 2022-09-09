#ifndef __HUMAIN_HEADER__
#define __HUMAIN_HEADER__

/* Ce module contient les fonctions de jeu et de don pour un joueur
   humain. A noter que les dites fonctions sont _interactives_.
   On utilise SGADE.
 */

#include <Socrates.h>
#include "HeartsEngine.h"
#include "Stuff.h"
#include "GameDisplayManagement.h"

void donnerCartesHumain(u8 joueur, u8 * buffer);

u8 jouerCarteHumain(u8 joueur);

#endif
