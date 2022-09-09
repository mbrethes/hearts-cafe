#ifndef __CARD_MANAGEMENT__
#define __CARD_MANAGEMENT__

#include <Socrates.h>
#include "Stuff.h"

// Définition des couleurs.
#define TREFLE  0
#define CARREAU 1
#define PIQUE   2
#define COEUR   3

#define NOMBRECOULEURS 4
#define NOMBREVALEURS  13
#define NOMBRECARTES   NOMBRECOULEURS*NOMBREVALEURS

// Les forces étant numérotées de 0 - le 2 à 12 - l'as
#define FORCEDAME      10

// Définition des états.
#define NONDIST 255
#define NONPRIS 255
#define NONCARTE 255
#define NONINIT 0xFFFF

typedef struct {
  u8 force;              // 0-12 pour 2-As
  u8 couleur;            // 0-3 (voir au dessus)
  u8 valeur;             // 1 pour chaque coeur, 13 dame de pique, 0 sinon.
  u8 possedeeParJoueur; 
  u8 priseParJoueur;
  u16 data;              // Peut contenir des données supplémentaires
                         // a la discrétion du programmeur.
                         // dans notre cas, contiendra l'index de sprite
                         // dans la mémoire OAM.
} carte;

typedef struct {
  carte lesCartes[NOMBRECARTES];
} jeuCartes;

// Fonctions associées.

void initialiserCartes(jeuCartes *leJeu);

void distribuerCartes(u8 nombreJoueurs, jeuCartes *leJeu);

bool aCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu);

bool peutJouerCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu);

void prendCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu);

#endif
