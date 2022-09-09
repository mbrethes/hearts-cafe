#ifndef __HEARTS_ENGINE__
#define __HEARTS_ENGINE__

/* Ce fichier contient les données, valeurs et fonctions utilisées dans la
   dame de pique.
*/

#include "CardManagement.h"
#include "GameDisplayManagement.h"
#include "IA.h"
#include "Humain.h"
#include "Player.h"
#include <Socrates.h>

// Variables

#define NOMBRE_JOUEURS 4
#define NOMBRE_CARTES_DONNE 3
#define PASJOUEE       NULL

#define NORMAL false
#define ANIME  true

#define COEFFCHG_NORMAL 100
#define TRUEVAL_NORMAL   50
#define COEFFCHG_ANIME   10
#define TRUEVAL_ANIME    5

#define PLAYER_JOHN 0
#define PLAYER_KAY  1
#define PLAYER_HCR  2
#define PLAYER_ELUF 3

// Si on n'est pas dans le fichier C correspondant...
#ifndef __IN_HEARTS_C__

extern joueur lesJoueurs[];

extern jeuCartes leJeu;

extern u8 carteJoueeSurLeTour[];

extern u8 carteDonneeAuDebut[];

extern u8 score[];

extern u8 premierJoueur;

extern bool coeurJoue;

extern bool damePiqueJouee;

extern bool etat[];

extern u8 nombrePlis;

#endif

// Fonctions membres

void initialiserScore();

void nouvellePartie();

bool calculerScore();

bool carteJouable(u8 joueur, u8 carte);

#endif
