#define __IN_HEARTS_C__

#include "HeartsEngine.h"

// Variables globales au module.

joueur lesJoueurs[NOMBRE_JOUEURS];

jeuCartes leJeu;

u8 carteJoueeSurLeTour[NOMBRE_JOUEURS];

u8 carteDonneeAuDebut[NOMBRE_JOUEURS * NOMBRE_CARTES_DONNE];

u8 score[NOMBRE_JOUEURS];

u8 premierJoueur;

bool coeurJoue;

bool damePiqueJouee;

u8 nombrePlis;

bool etat[NOMBRE_JOUEURS];

// Cette fonction termine les initialisations des joueurs.
// SI un des joueurs est une IA, elle demande à ce joueur
// de définir sa stratégie initiale.
void initFinalJoueurs() {
  u8 i;

  for (i = 0 ; i < NOMBRECARTES ; i++) {
    lesJoueurs[leJeu.lesCartes[i].possedeeParJoueur].quiPossede[i] = leJeu.lesCartes[i].possedeeParJoueur;
  }

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (lesJoueurs[i].type != TYPE_HUMAIN)
      definirStrategieInitiale(i);
  }
}

// Cette fonction demande à chaque joueur de donner 3
// de ses cartes, grâce à la fonction "donnerCartes"
// que chaque joueur a implémentée dans son code.
// Les cartes transitent par un buffer commun aux
// joueurs : donneeAuDebut.
void donner3Cartes() {
  u8 i, j;
  
  for (i = 0; i < NOMBRE_JOUEURS ; i++) {
    GDMmettreAJourAffichage(i, NONCARTE, PHASE_DEBUT_TOUR);

    // D'abord on donne les cartes...
    switch (lesJoueurs[i].type) {
    case TYPE_HUMAIN:
      donnerCartesHumain(i, & carteDonneeAuDebut[i * NOMBRE_CARTES_DONNE]);
      break;
    case TYPE_IA_BAS:
      donnerCartesIABasic(i, & carteDonneeAuDebut[i * NOMBRE_CARTES_DONNE]);
      break;
    case TYPE_IA_ALE:
    default:
      donnerCartesIAAlea(i, & carteDonneeAuDebut[i * NOMBRE_CARTES_DONNE]);
    }

    GDMmettreAJourAffichage(i, NONCARTE, PHASE_FIN_TOUR);
  }

  // Ensuite, on les fait passer au joueur suivant.
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    
    for (j = 0 ; j < NOMBRE_CARTES_DONNE ; j++) {
      // On les passe au joueur de gauche...
      leJeu.lesCartes[carteDonneeAuDebut[(i * NOMBRE_CARTES_DONNE) + j]].possedeeParJoueur = SoMathModulus(i + 1, NOMBRE_JOUEURS);
      lesJoueurs[i].quiPossede[carteDonneeAuDebut[(i * NOMBRE_CARTES_DONNE) + j]] = SoMathModulus(i + 1, NOMBRE_JOUEURS);
    }
  }

  // Enfin on réinitialise le tableau.
  for (i = 0 ; i < NOMBRE_CARTES_DONNE * NOMBRE_JOUEURS ; i++) {
    carteDonneeAuDebut[i] = NONCARTE;
  }
}

// Renvoie le numéro du joueur qui a le 2 de trèfle.
u8 quiCommence() {
  return leJeu.lesCartes[0].possedeeParJoueur;
}

// Renvoie true si la carte 2 est plus forte que la carte 1.
// Renvoie false sinon.
bool cartePlusForte(u8 carte1, u8 carte2) {
  // si les couleurs sont différentes, la carte la plus forte est la première.
  if (leJeu.lesCartes[carte1].couleur != leJeu.lesCartes[carte2].couleur)
    return false;
  
  return leJeu.lesCartes[carte1].force < leJeu.lesCartes[carte2].force;
}

// Cette fonction renvoie le numéro du joueur qui a gagné
// le pli courant.
u8 determinerPli() {
  u8 joueurGagnant;
  u8 i;

  joueurGagnant = premierJoueur;

  // On détermine le gagnant
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (cartePlusForte(carteJoueeSurLeTour[joueurGagnant], carteJoueeSurLeTour[i]))
      joueurGagnant = i;
  }

  // On indique que c'est lui qui a pris le pli
  // On indique également que les cartes ont été prises
  // On vérifie également si un coeur a été joué.
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    leJeu.lesCartes[carteJoueeSurLeTour[i]].priseParJoueur = joueurGagnant;
    // leJeu.lesCartes[carteJoueeSurLeTour[i]].possedeeParJoueur = NONDIST;
    if (leJeu.lesCartes[carteJoueeSurLeTour[i]].couleur == COEUR) coeurJoue = true;
    
  }
  
  // Et on redéfinit la stratégie des IAs.
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (lesJoueurs[i].type != TYPE_HUMAIN) {
      redefinirStrategie(i);
    }
  }

  return joueurGagnant;
}

// Cette fonction est la principale du programme. Chaque
// joueur va jouer à tour de rôle, remplissant le tableau
// "carteJoueeSurLeTour".
// Elle renvoie le numéro du joueur qui a remporté le
// pli.
u8 tourDeJeu() {
  u8 i;
  u8 gagnant;

  // Ne pas oublier de réinitialiser le tableau à chaque fois !
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    carteJoueeSurLeTour[i] = NONCARTE;
  }

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {

    GDMmettreAJourAffichage(SoMathModulus(i + premierJoueur, NOMBRE_JOUEURS), carteJoueeSurLeTour[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)], PHASE_DEBUT_TOUR);
    // afficherEcranJeuPrincipal(i);
    switch (lesJoueurs[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)].type) {
    case TYPE_HUMAIN:
      carteJoueeSurLeTour[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)] = jouerCarteHumain( SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS));
      break;
    case TYPE_IA_BAS:
      carteJoueeSurLeTour[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)] = jouerCarteIABasic(SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS));
      break;
    case TYPE_IA_ALE:
    default:
      carteJoueeSurLeTour[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)] = jouerCarteIAAlea(SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS));
      break;
    }
    leJeu.lesCartes[carteJoueeSurLeTour[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)]].possedeeParJoueur = NONDIST;

    GDMmettreAJourAffichage(SoMathModulus(i + premierJoueur, NOMBRE_JOUEURS), carteJoueeSurLeTour[SoMathModulus((i + premierJoueur), NOMBRE_JOUEURS)], PHASE_FIN_TOUR);
    // afficherEcranJeuPrincipal(i);
    
  }
  
  // afficherDemandeConfirmation();

  // GDMinitialiserEcranJeu();
  // GDMmettreAJourAffichage(0, 0);

  // while (1);

  // keyPressWait();

  gagnant = determinerPli();

  GDMafficherEcranRecapitulatifPli(gagnant, premierJoueur);

  return gagnant;
}

// Crée et fait jouer une partie de dame de pique.
// Distribue les cartes, etc.
// On suppose les joueurs initialisés par une fonction
// de plus haut niveau.
void nouvellePartie() {
  u8 i;

  initialiserCartes(& leJeu);

  // SoMode4RendererDrawString  (0, 240, 8,"TestNouvellePartie", SoFontGetDefaultFontImage());

  // SoMode4RendererFlip  ();

  // Bug ?
  distribuerCartes(NOMBRE_JOUEURS, & leJeu);

  // for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
  //   afficherJeu(i);
  //   keyPressWait();
  // }

  initFinalJoueurs();

  coeurJoue = false;
  damePiqueJouee = false;
  
  
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    carteJoueeSurLeTour[i] = NONCARTE;
  }

  for (i = 0 ; i < NOMBRE_JOUEURS * NOMBRE_CARTES_DONNE ; i++) {
    carteDonneeAuDebut[i] = NONCARTE;
  }

  donner3Cartes();

  premierJoueur = quiCommence();

  for (nombrePlis = 0 ; nombrePlis < (NOMBRECARTES / NOMBRE_JOUEURS) ; nombrePlis++) 
    premierJoueur = tourDeJeu();

  
  
}

// Initialise le score de tous les joueurs à 0
void initialiserScore() {
  u8 i;

  for ( i = 0 ; i < NOMBRE_JOUEURS ; i++) 
    score[i] = 0;
}

// Cette fonction calcule le score de chaque joueur,
// pour la partie qui vient de s'écouler. Retourne 
// "true" s'il y a au moins un perdant après calcul.
bool calculerScore() {
  u8 i, j;
  u8 nvscore[NOMBRE_JOUEURS];
  u8 winner = 0;
  bool shdamoon = false;

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    nvscore[i] = 0;
  }

  for (i = 0 ; i < NOMBRECARTES ; i++)
    nvscore[leJeu.lesCartes[i].priseParJoueur] += leJeu.lesCartes[i].valeur;
  
  // A-t-on tiré la lune ?
  i = 0;
  while (i < NOMBRE_JOUEURS) {
    if (nvscore[i] < nvscore[winner]) {
      winner = i;
    }
    if (nvscore[i] == 26) {
      for (j = 0 ; j < NOMBRE_JOUEURS ; j++)
	nvscore[j] = 26;
      nvscore[i] = 0;
      winner = i;
      shdamoon = true;
      break;
    }
    i++;
  }

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    score[i] += nvscore[i];
  }

  GDMafficherScore(shdamoon);

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++)
    if (score[i] >= 100) return true;

  return false;
}

// Cette fonction renvoie true si la carte dont l'indice est donné
// en paramètre est jouable dans le contexte du pli courant.
bool carteJouable(u8 joueur, u8 carte) {
  u8 i;
  bool coeurOnly = true;
  bool pointsOnly = true;
  // si on est au premier tour, premier joueur, on ne peut jouer que le
  // 2 de trèfle.
  if (nombrePlis == 0 && premierJoueur == joueur)
    return carte == 0;

  // Si on a que du coeur dans sa main, on ne peut que le jouer)

  for (i = 0 ; i < NOMBRECARTES ; i++) {
    if (leJeu.lesCartes[i].couleur != COEUR && leJeu.lesCartes[i].possedeeParJoueur == joueur) {
      coeurOnly = false;
    }
    if (leJeu.lesCartes[i].valeur == 0 && leJeu.lesCartes[i].possedeeParJoueur == joueur)
      pointsOnly = false;
  }

  if (coeurOnly == true) return true;

  // si on est le premier joueur, dans les autres cas :
  // on joue ce qu'on veut, sauf coeur si coeur n'a pas été joué.
  if (joueur == premierJoueur)
    return ! (leJeu.lesCartes[carte].couleur == COEUR && ! coeurJoue);
  
  // cas général :
  
  // au premier tour, interdit de jouer des points (sauf si on a que ça)
  if (nombrePlis == 0 && leJeu.lesCartes[carte].valeur > 0 && !pointsOnly)
    return false;

  // Si la carte est de la même couleur que la carte du premier joueur
  // c'est OK

  if (leJeu.lesCartes[carte].couleur == leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur)
    return true;

  // Si la carte n'est pas de la même couleur, vérifier que le joueur ne
  // dispose pas de cartes de la couleur, et retourner true si c'est le cas.
  
  for (i = 0 ; i < NOMBRECARTES ; i++) {
    // si le joueur possède une carte de la même couleur, on renvoie faux.
    if ((leJeu.lesCartes[i].possedeeParJoueur == joueur) && (leJeu.lesCartes[i].couleur == leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur))
      return false;
  }

  // cas général : on renvoie vrai !
  return true;
}
