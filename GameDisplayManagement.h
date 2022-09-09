#ifndef __GAME_DISP_MGT_HEADER__
#define __GAME_DISP_MGT_HEADER__

/* Ce module contient les fonctions d'affichage réclamées - à cors et
   à cris - par les développeurs... */

#include <Socrates.h>
#include "HeartsEngine.h"
#include "Palettes.h"
#include "Player.h"
#include "DiversSprites.h"
#include "CoeurSprites.h"
#include "PiqueSprites.h"
#include "TrefleSprites.h"
#include "CarreauSprites.h"
#include "Stuff.h"
#include "GameTiles.h"

// #define globaux

#define PHASE_DEBUT_TOUR 0
#define PHASE_FIN_TOUR   1
#define PHASE_AUTRE      2
#define PHASE_DON        3

// Nouvelles fonctions

void GDMinitialiserEcranJeu();

void GDMmettreAJourAffichage(u8 joueur_courant, u8 carte_selectionnee, u8 phase);

void GDMafficherEcranAttente(u8 joueur_courant);

bool GDMafficherEcranConfirmation(u8 joueur_courant);

void GDMafficherEcranRecapitulatifPli(u8 joueur_gagnant, u8 premier_joueur);

void GDManimationShootDaMoon();

void GDMafficherScore(bool shdamoon);

void GDMlibererEcranJeu();

#endif
