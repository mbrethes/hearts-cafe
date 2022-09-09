#ifndef __PLAYER_HEADER__
#define __PLAYER_HEADER__

/* Le fichier d'entete des joueurs */

#include <Socrates.h>
#include "CardManagement.h"

#define LONGUEUR_MINI 3
#define LONGUEUR_NOM 4

#define TYPE_HUMAIN 0
#define TYPE_IA_ALE 1
#define TYPE_IA_BAS 2

typedef struct {
  u8 type;
  char nom[LONGUEUR_NOM + 1];
  u8 quiPossede[NOMBRECARTES];
  bool shoot_da_moon;
} joueur;

// Fonctions membres

void initialiserJoueur(joueur *leJoueur, u8 type, char *nom);

#endif
