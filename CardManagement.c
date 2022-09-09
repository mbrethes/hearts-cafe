#include "CardManagement.h"

// Initialise le jeu pour jouer à la dame de pique.
void initialiserCartes(jeuCartes *leJeu) {
  u8 carteCourante;

  for (carteCourante = 0 ; carteCourante < NOMBRECARTES ; carteCourante++) {
    leJeu->lesCartes[carteCourante].force = carteCourante % NOMBREVALEURS;
    leJeu->lesCartes[carteCourante].couleur = carteCourante / NOMBREVALEURS;

    if (leJeu->lesCartes[carteCourante].couleur == COEUR)
      leJeu->lesCartes[carteCourante].valeur = 1;
    else if (leJeu->lesCartes[carteCourante].couleur == PIQUE && leJeu->lesCartes[carteCourante].force == FORCEDAME)
      leJeu->lesCartes[carteCourante].valeur = 13;
    else
      leJeu->lesCartes[carteCourante].valeur = 0;

    leJeu->lesCartes[carteCourante].possedeeParJoueur = NONDIST;
    leJeu->lesCartes[carteCourante].priseParJoueur = NONPRIS;
    leJeu->lesCartes[carteCourante].data = NONINIT;
  }
}

// Répartit les cartes entre les joueurs.
// On suppose que le nombre de cartes est un multiple du nombre de
// joueurs.
void distribuerCartes(u8 nombreJoueurs, jeuCartes *leJeu) {
  u8 joueurCourant;
  u8 carteCourante;
  char cnum[6];
  char ctst[6];
  ctst[5] = 0;
  cnum[5] = 0;
  u8 i;


  // les joueurs sont numérotés à partir de 0.
  for (joueurCourant = 0 ; joueurCourant < nombreJoueurs ; joueurCourant ++) {

    for (i = 0 ; i < (NOMBRECARTES / nombreJoueurs) ; i++) {

      carteCourante = SoMathModulus(SoMathRand(), NOMBRECARTES);

      // si la carte est déjà prise...
      while (leJeu->lesCartes[carteCourante].possedeeParJoueur != NONDIST) {
	
	carteCourante = SoMathModulus((carteCourante + 1), NOMBRECARTES);
      }
      leJeu->lesCartes[carteCourante].possedeeParJoueur = joueurCourant;

      //exit(0);
    }
  }
}

// Renvoie "true" si le joueur donné possède la carte courante dans
// sa main.
bool aCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu) {
  return leJeu->lesCartes[force * couleur].possedeeParJoueur == leJoueur;
}

// Renvoie "true" si le joueur possède la carte ET si elle n'a pas été prise.
bool peutJouerCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu) {
  return aCarte(leJoueur, couleur, force, leJeu) && leJeu->lesCartes[force * couleur].priseParJoueur == NONPRIS;
}

// Met à jour le tableau des cartes en indiquant que la carte est prise.
void prendCarte(u8 leJoueur, u8 couleur, u8 force, jeuCartes *leJeu) {
  leJeu->lesCartes[force * couleur].priseParJoueur = leJoueur;
}

