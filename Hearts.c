#include <Socrates.h>
#include "Intro.h"
#include "GameMenu.h"
#include "Mods.h"
#include "Player.h"

/**

    Main Starting point of Hearts Cafe.
    Copyright (C) 2002 by Mathieu Brèthes (contact me via GitHub).

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
