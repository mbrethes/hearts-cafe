#ifndef __MENUDISPLAYMGT_HEADER__
#define __MENUDISPLAYMGT_HEADER__

#include <Socrates.h>
#include "DiversSprites.h"
#include "Palettes.h"
#include "Stuff.h"
#include "HeartsEngine.h"
#include "GameBitmaps.h"

void MDMinitialiserEcranMenu();

void MDMlibererEcranMenu();

void MDMafficherMenuSelectionJoueurs(u8 nombreSelectionne, u8 typeJoueur);

bool MDMselectionnerNomJoueur(char *s, u8 lenmin, u8 lenmax);

#endif
