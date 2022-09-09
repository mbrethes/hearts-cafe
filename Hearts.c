#include <Socrates.h>
#include "Intro.h"
#include "GameMenu.h"
#include "Mods.h"
#include "Player.h"

// Ne semble pas fonctionner...

// # define MULTIBOOT int __gba_multiboot;

// MULTIBOOT

void AgbMain() {

  u8 i;
  char a = 0;

  u32 seed;

  SoDisplayInitialize();

  // afm_install();

  seed = InitIntro();

  SoMathRandSeed(GameSplashScreen(seed));

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    initialiserJoueur(& lesJoueurs[i], TYPE_HUMAIN, & a);
  }

  while(1) GameMenu();
  
}
