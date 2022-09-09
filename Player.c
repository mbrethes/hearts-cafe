#include "Player.h"

void initialiserJoueur(joueur *leJoueur, u8 type, char* nom) {
  u8 i;

  for (i = 0 ; i < LONGUEUR_NOM + 1; i++)
    leJoueur->nom[i] = 0;

  leJoueur->type = type;
  for (i = 0 ; i < LONGUEUR_NOM && nom[i] != 0 ; i++) {
    leJoueur->nom[i] = nom[i];
  }

  for(i = 0 ; i < NOMBRECARTES ; i++) {
    leJoueur->quiPossede[i] = 0;
  }
}
