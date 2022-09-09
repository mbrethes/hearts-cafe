#ifndef __CARD_MANAGEMENT__
#define __CARD_MANAGEMENT__

#include <Socrates.h>
#include "Stuff.h"

// D�finition des couleurs.
#define TREFLE  0
#define CARREAU 1
#define PIQUE   2
#define COEUR   3

#define NOMBRECOULEURS 4
#define NOMBREVALEURS  13
#define NOMBRECARTES   NOMBRECOULEURS*NOMBREVALEURS

// Les forces �tant num�rot�es de 0 - le 2 � 12 - l'as
#define FORCEDAME      10

// D�finition des �tats.
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
  u16 data;              // Peut contenir des donn�es suppl�mentaires
                         // a la discr�tion du programmeur.
                         // dans notre cas, contiendra l'index de sprite
                         // dans la m�moire OAM.
} carte;

typedef struct {
  carte lesCartes[NOMBRECARTES];
} jeuCartes;

// Fonctions associ�es.

void initialiserCartes(jeuCartes *leJeu);

void distribuerCartes(u8 nombreJoueurs, jeuCartes *leJeu);

bool aCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu);

bool peutJouerCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu);

void prendCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu);

#endif
