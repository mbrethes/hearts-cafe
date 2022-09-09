#ifndef __INTRO_HEADER__
#define __INTRO_HEADER__

#include <Socrates.h>

#include "Palettes.h"
#include "GameBitmaps.h"
// D�claration de proc�dures et fonctions.

u32 InitIntro();

// Renvoie un entier correspondant � la "graine" (le moment entre lequel
// l'utilisateur arrive sur le menu et celui o� il appuie sur Start...)
u32 GameSplashScreen(u32 seed);

#endif
