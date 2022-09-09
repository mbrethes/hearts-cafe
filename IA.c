#include "IA.h"

// Cette fonction définit la stratégie initiale d'un joueur
// donné. Il s'agit tout betement ici de mettre à true ou
// false le flag "shoot_da_moon".
void definirStrategieInitiale(u8 joueur) {
  switch (lesJoueurs[joueur].type)
    {
    case TYPE_IA_ALE:
    default:
      lesJoueurs[joueur].shoot_da_moon = false;
    }
}

// Redéfinit la stratégie du joueur IA donné (flag shoot_da_moon)
// en fonction du pli qui vient d'être fait.
void redefinirStrategie(u8 joueur) {
  switch (lesJoueurs[joueur].type)
    {
    case TYPE_IA_ALE:
    default:
      lesJoueurs[joueur].shoot_da_moon = false;
    }
}

// Cette fonction donne 3 cartes au hasard du jeu.
void donnerCartesIAAlea(u8 joueur, u8* buffer) {
  u8 i, j, k;
  u8 curCard;

  for (i = 0 ; i < NOMBRE_CARTES_DONNE ; i++) {
    curCard = SoMathRand() % ((NOMBRECARTES / NOMBRE_JOUEURS) - i) + 1;
    k = 0;
    for (j = 0 ; j < NOMBRECARTES && k < curCard; j++)
      if (leJeu.lesCartes[j].possedeeParJoueur == joueur) k++;

    // ...
    buffer[i] = j - 1;
    leJeu.lesCartes[j-1].possedeeParJoueur = NONDIST;
  }
}

// Cette fonction sélectionne une carte jouable au hasard du jeu
// et la met sur le terrain.
u8 jouerCarteIAAlea(u8 joueur) {
  u8 j, k;
  u8 curCard;

  do {
    curCard = SoMathRand() % ((NOMBRECARTES / NOMBRE_JOUEURS) - nombrePlis) + 1;
    k = 0 ;
    for (j = 0 ; j < NOMBRECARTES && k < curCard; j++)
      if (leJeu.lesCartes[j].possedeeParJoueur == joueur) k++;

  } while (! carteJouable(joueur, j - 1));

  return j - 1;
}

// Renvoie le nombre de cartes possédées par un joueur dans une couleur.
u8 nombreCartesCouleur(u8 joueur, u8 couleur) {
  u8 i;
  u8 nbc = 0;

  for (i = 0 ; i < 52 ; i++) {
    if (leJeu.lesCartes[i].couleur == couleur && leJeu.lesCartes[i].possedeeParJoueur == joueur) nbc++;
  }

  return nbc;
}

// Cette fonction choisit 3 cartes à donner. En priorité :
// 1. la dame de pique si on l'a
// 2. les piques au-dessus de la dame (roi, as).
// 3. des cartes les plus fortes possibles, priorité aux coupes (le moins
//    de cartes à la couleur)
void donnerCartesIABasic(u8 joueur, u8* buffer) {
  u8 i, k;
  s16 j;
  u8 tmp;
  bool found;

  u8 nbCouleurs[4];
  u8 indices[4];

  nbCouleurs[TREFLE] = nombreCartesCouleur(joueur, TREFLE);
  nbCouleurs[CARREAU] = nombreCartesCouleur(joueur, CARREAU);
  nbCouleurs[PIQUE] = nombreCartesCouleur(joueur, PIQUE);
  nbCouleurs[COEUR] = nombreCartesCouleur(joueur, COEUR);
  indices[TREFLE] = TREFLE;
  indices[CARREAU] = CARREAU;
  indices[PIQUE] = PIQUE;
  indices[COEUR] = COEUR;
  
  for (i = 0 ; i < NOMBRE_CARTES_DONNE ; i++) {

    // 0. Trier le tableau d'indices.

    for (j = 3 ; j > 0 ; j--) {
      for (k = 0 ; k < j ; k++) {
	if (nbCouleurs[k] > nbCouleurs[j]) {
	  tmp = nbCouleurs[k];
	  nbCouleurs[k] = nbCouleurs[j];
	  nbCouleurs[j] = tmp;
	  tmp = indices[k];
	  indices[k] = indices[j];
	  indices[j] = tmp;
	}
      }
    }

    // 1. A-t-on la dame de pique ?
    if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME].possedeeParJoueur == joueur) {
      // Oui, on la donne ;)
      buffer[i] = (PIQUE * NOMBREVALEURS) + FORCEDAME;
      leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME].possedeeParJoueur = NONDIST;
    }
    // 2. A-t-on l'as de pique, supérieur à la dame ?
    else if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME + 2].possedeeParJoueur == joueur) {
      // Oui, on le donne :)
      buffer[i] = (PIQUE * NOMBREVALEURS) + FORCEDAME + 2;
      leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME + 2].possedeeParJoueur = NONDIST;
    }
    // 3. A-t-on le roi de pique ?
    else if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME + 1].possedeeParJoueur == joueur) {
      // Oui, on le donne :)
      buffer[i] = (PIQUE * NOMBREVALEURS) + FORCEDAME + 1;
      leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME + 1].possedeeParJoueur = NONDIST;
    }
    // 4. A-t-on des cartes fortes ? (sont prioritaires les couleurs
    // dont on a le moins de cartes)
    else {
      found = false;
      for (j = 12 ; j >= 0 && found == false ; j--) {
	for (k = 0 ; k < 4 && found == false ; k++) {
	  if (leJeu.lesCartes[(indices[k] * NOMBREVALEURS) + j].possedeeParJoueur == joueur) {
	    found = true;
	    buffer[i] = (indices[k] * NOMBREVALEURS) + j;
	    nbCouleurs[indices[k]] --;
	    leJeu.lesCartes[(indices[k] * NOMBREVALEURS) + j].possedeeParJoueur = NONDIST;
	  }
	}
      }
    }
  }    
}

// Renvoie "vrai" si on est le premier à jouer.
bool jouerEnPremier(u8 joueur) {
  return joueur == premierJoueur;
}

// REnvoie "vrai" si on est le dernier à jouer.
bool jouerEnDernier(u8 joueur) {
  return SoMathModulus(joueur + 1, NOMBRE_JOUEURS) == premierJoueur;
}

// Renvoie "vrai" s'il faut couper
bool doitCouper(u8 joueur) {
  u8 i;

  for (i = 0 ; i < NOMBRECARTES ; i++) {
    if (leJeu.lesCartes[i].possedeeParJoueur == joueur && leJeu.lesCartes[i].couleur == leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur)
      return false;
  }
  
  return true;
}

// Renvoie l'indice de la carte qui pour le moment remporte le pli.
u8 carteRemportePli() {
  u8 i;
  u8 carteMax = carteJoueeSurLeTour[premierJoueur];

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (carteJoueeSurLeTour[i] != NONCARTE) {
      if (leJeu.lesCartes[carteJoueeSurLeTour[i]].force > leJeu.lesCartes[carteMax].force && leJeu.lesCartes[carteJoueeSurLeTour[i]].couleur == leJeu.lesCartes[carteMax].couleur) {
	carteMax = carteJoueeSurLeTour[i];
      }
    }
  }

  return carteMax;
}

// Renvoie l'indice de la carte la plus forte jouable
// si le joueur peut, avec ses cartes, ne pas remporter
// le pli. On suppose qu'il a des cartes de la couleur (au moins 1).
// Renvoie noncarte sinon.
u8 peutPerdre(u8 joueur) {
  u8 couleur;
  u8 force;
  u8 i;

  u8 carteMax;

  carteMax = carteRemportePli();

  couleur = leJeu.lesCartes[carteMax].couleur;
  force   = leJeu.lesCartes[carteMax].force;
  
  for (i = (couleur * NOMBREVALEURS) + force ; i > (couleur * NOMBREVALEURS) ; i --) {
    if (leJeu.lesCartes[i - 1].possedeeParJoueur == joueur)
      return i - 1;
  }

  return NONCARTE;
}

// La coupe.
// La coupe de l'IA basique est simple : on coupe en priorité avec des
// points (dame de pique, coeurs), puis avec des cartes élevées / priorité
// aux longues, toujours plus difficiles à passer !
u8 couperCarteIABasic(u8 joueur) {
  u8 i, j, k;
  u8 tmp;
  
  u8 nbCouleurs[4];
  u8 indices[4];

  nbCouleurs[TREFLE] = nombreCartesCouleur(joueur, TREFLE);
  nbCouleurs[CARREAU] = nombreCartesCouleur(joueur, CARREAU);
  nbCouleurs[PIQUE] = nombreCartesCouleur(joueur, PIQUE);
  nbCouleurs[COEUR] = nombreCartesCouleur(joueur, COEUR);
  indices[TREFLE] = TREFLE;
  indices[CARREAU] = CARREAU;
  indices[PIQUE] = PIQUE;
  indices[COEUR] = COEUR;
  
  // 0. Trier en inverse le tableau d'indices.
  
  for (j = 3 ; j > 0 ; j--) {
    for (k = 0 ; k < j ; k++) {
      if (nbCouleurs[k] < nbCouleurs[j]) {
	  tmp = nbCouleurs[k];
	  nbCouleurs[k] = nbCouleurs[j];
	  nbCouleurs[j] = tmp;
	  tmp = indices[k];
	  indices[k] = indices[j];
	  indices[j] = tmp;
      }
    }
  }

  // 1. A-t-on la dame de pique ? Si oui, on coupe avec...
  if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME].possedeeParJoueur == joueur) {
    if (carteJouable(joueur, (PIQUE * NOMBREVALEURS) + FORCEDAME))
      return  (PIQUE * NOMBREVALEURS) + FORCEDAME;
  }
  
  // 2. A-t-on des coeurs ? Si oui, on coupe avec...
  if (nbCouleurs[indices[COEUR]] > 0) {
    for (j = NOMBREVALEURS ; j > 0 ; j--) {
      if (leJeu.lesCartes[(COEUR * NOMBREVALEURS) + j - 1].possedeeParJoueur == joueur) {
	if (carteJouable(joueur, (COEUR * NOMBREVALEURS) + j - 1))
	  return (COEUR * NOMBREVALEURS) + j - 1;
      }
    }
  }

  // 3. A-t-on le roi ou l'as de pique ? Si oui, on coupe en priorité avec...
  if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME + 2].possedeeParJoueur == joueur) {
    // Oui, on le donne :)
    if (carteJouable(joueur,  (PIQUE * NOMBREVALEURS) + FORCEDAME + 2)) 
      return (PIQUE * NOMBREVALEURS) + FORCEDAME + 2;
  }
  if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME + 1].possedeeParJoueur == joueur) {
    // Oui, on le donne :)
    if (carteJouable(joueur,  (PIQUE * NOMBREVALEURS) + FORCEDAME + 1)) 
      return (PIQUE * NOMBREVALEURS) + FORCEDAME + 1;
  }

  // 4. Cas général : couper avec une carte forte, priorité sur égalité aux
  // longues.

  for (i = 0 ; i < 4 ; i++) {
    for (j = NOMBREVALEURS ; j > 0 ; j --) {
      if (leJeu.lesCartes[(indices[i] * NOMBREVALEURS) + j - 1].possedeeParJoueur == joueur) {
	if (carteJouable(joueur, (indices[i] * NOMBREVALEURS) + j - 1))
	  return (indices[i] * NOMBREVALEURS) + j - 1;
      }
    }
  }
  
  // On  ne devrait jamais arriver ici !

  SO_ASSERT(false, "Erreur coupe du joueur !!!");
  return NONCARTE;
}

// Le jeu.
// Si on est le premier à jouer, on joue une carte la plus faible possible.
// Si on est le dernier à jouer : si on ne peut pas perdre, on prend avec la
// plus forte, en utilisant si possible roi/as de pique si possible.
// (en faisant attention à n'utiliser la dame de pique qu'en
// dernière extrémité). Sinon on pose la carte la plus forte en-dessous (ou la
// dame de pique si on peut).
// Si on est en cours de partie : soit on joue juste en dessous pour ne pas
// gagner (priorité à la dame de pique), soit on joue juste au-dessus.
u8 jouerCarteIABasic(u8 joueur) {
  u8 i, j, k;
  u8 tmp;

  u8 nbCouleurs[4];
  u8 indices[4];

  nbCouleurs[TREFLE] = nombreCartesCouleur(joueur, TREFLE);
  nbCouleurs[CARREAU] = nombreCartesCouleur(joueur, CARREAU);
  nbCouleurs[PIQUE] = nombreCartesCouleur(joueur, PIQUE);
  nbCouleurs[COEUR] = nombreCartesCouleur(joueur, COEUR);
  indices[TREFLE] = TREFLE;
  indices[CARREAU] = CARREAU;
  indices[PIQUE] = PIQUE;
  indices[COEUR] = COEUR;

  // 0. Trier le tableau d'indices.
  
  for (j = 3 ; j > 0 ; j--) {
    for (k = 0 ; k < j ; k++) {
      if (nbCouleurs[k] > nbCouleurs[j]) {
	  tmp = nbCouleurs[k];
	  nbCouleurs[k] = nbCouleurs[j];
	  nbCouleurs[j] = tmp;
	  tmp = indices[k];
	  indices[k] = indices[j];
	  indices[j] = tmp;
      }
    }
  }

  // 1er grand cas : si on joue en premier.
  
  if (jouerEnPremier(joueur)) {
    // on joue donc : le 2 de trèfle si on l'a (premier tour)
    if (leJeu.lesCartes[0].possedeeParJoueur == joueur) {
      if (carteJouable(joueur, 0))
	return 0;
    }

    // une petite carte jouable sinon, priorité à la création de
    // coupes (on consomme les cartes des coupes), dame de pique
    // interdite.

    for (i = 0 ; i < NOMBREVALEURS ; i++) {
      for (j = 0 ; j < 4 ; j++) {
	if (leJeu.lesCartes[(indices[j] * NOMBREVALEURS) + i].possedeeParJoueur == joueur) {
	  if (! ( leJeu.lesCartes[(indices[j] * NOMBREVALEURS) + i].couleur == PIQUE && leJeu.lesCartes[(indices[j] * NOMBREVALEURS) + i].force == FORCEDAME)) {
	    if (carteJouable(joueur, (indices[j] * NOMBREVALEURS) + i))
	      return (indices[j] * NOMBREVALEURS) + i;
	  }
	}
      }
    }
    // Si on est là, c'est qu'on a rien pu jouer d'autre 
    // (cas extrème : 12 coeurs et la dame de pique, ou plus que la dame
    // en question !!!).
    // On joue donc la dame de pique.
    if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME].possedeeParJoueur == joueur) {
      if (carteJouable(joueur, (PIQUE * NOMBREVALEURS) + FORCEDAME))
	return (PIQUE * NOMBREVALEURS) + FORCEDAME;
    }

    // ne devrait jamais arriver...
    SO_ASSERT(false, "Impossible de jouer en premier ?");
  }
  // Cas numéro 2 : si on ne joue pas en premier, et qu'on doit couper...
  if (doitCouper(joueur))
    return couperCarteIABasic(joueur);
  
  // Cas numéro 3 : on joue en dernier.
  if (jouerEnDernier(joueur)) {
    // Sous-cas 1 : peut-on perdre ?
    if ( (tmp = peutPerdre(joueur)) != NONCARTE) {
      // Oui, on joue la plus forte en-dessous...
      if (carteJouable(joueur, tmp))
	return tmp;
    } else {
      // Non, on joue la plus forte au-dessus... Sauf s'il s'agit de la
      // dame de pique !
      for (i = NOMBREVALEURS ; i > 0 ; i--) {
	if (leJeu.lesCartes[(leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur * NOMBREVALEURS) + i - 1].possedeeParJoueur == joueur) {
	  // Si ce n'est pas la dame de pique...
	  if (! ( leJeu.lesCartes[(leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur * NOMBREVALEURS) + i - 1].couleur == PIQUE && leJeu.lesCartes[(leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur * NOMBREVALEURS) + i - 1].force == FORCEDAME)) {
	    if (carteJouable(joueur, (leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur * NOMBREVALEURS) + i - 1))
	      return (leJeu.lesCartes[carteJoueeSurLeTour[premierJoueur]].couleur * NOMBREVALEURS) + i - 1;
	  }
	}
      }
      // Si on est ici, c'est qu'on a plus que la dame de pique à jouer...

      if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME].possedeeParJoueur == joueur) {
	if (carteJouable(joueur, (PIQUE * NOMBREVALEURS) + FORCEDAME))
	  return (PIQUE * NOMBREVALEURS) + FORCEDAME;
      }
      // On ne devrait jamais arriver ici
      SO_ASSERT(false, "Impossible de jouer en dernier ?");
    }
  }
    
  // Cas général : on joue au milieu.
  
  // Si on peut perdre, on le fait...
  if ((tmp = peutPerdre(joueur)) != NONCARTE) {
    if (carteJouable(joueur, tmp))
      return tmp;
    
    // ne devrait jamais arriver
    SO_ASSERT(false, "Impossible perdre !");
  } else {
    // Si on ne peut pas perdre, on joue la plus faible au-dessus, à 
    // l'exception de la dame de pique si on l'a.
    tmp = carteRemportePli();

    // Pique ?

    if (leJeu.lesCartes[tmp].couleur == PIQUE) {

      for (i = tmp ; i < ((PIQUE + 1) * NOMBREVALEURS) ; i++)
	{
	  // Pas la dame de pique...
	  if (leJeu.lesCartes[i].force != FORCEDAME) {
	    if (leJeu.lesCartes[i].possedeeParJoueur == joueur) {
	      if (carteJouable(joueur, i))
		return i;
	    }
	  }
	}
      // Si on est là, il ne reste que la dame à jouer...
      if (leJeu.lesCartes[(PIQUE * NOMBREVALEURS) + FORCEDAME].possedeeParJoueur == joueur) {
	if (carteJouable(joueur, (PIQUE * NOMBREVALEURS) + FORCEDAME))
	  return (PIQUE * NOMBREVALEURS) + FORCEDAME;
      }

      // Ne devrait jamais arriver...
      SO_ASSERT(false, "Impossible jouer pique milieu");
    } 
    // Cas général...
    else {
      for (i = tmp ; i < ((leJeu.lesCartes[tmp].couleur + 1) * NOMBREVALEURS) ; i++)
	{
	  if (leJeu.lesCartes[i].possedeeParJoueur == joueur) {
	    if (carteJouable(joueur, i))
	      return i;
	  }
	}

      // Ne devrait jamais arriver...
      SO_ASSERT(false, "Impossible de joueur couleur milieu");
    }
  }

  // On ne devrait jamais venir ici...
  SO_ASSERT(false, "ERRIA");
  return NONCARTE;
}
