#ifndef __INTRO_HEADER__
#define __INTRO_HEADER__

#include <Socrates.h>

#include "Palettes.h"
#include "GameBitmaps.h"
// Déclaration de procédures et fonctions.

u32 InitIntro();

// Renvoie un entier correspondant à la "graine" (le moment entre lequel
// l'utilisateur arrive sur le menu et celui où il appuie sur Start...)
u32 GameSplashScreen(u32 seed);

#endif
