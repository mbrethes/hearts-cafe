#include "Humain.h"

// Cette fonction est une fonction interactive de sélection de la carte à
// donner / jouer.
u8 selectionCarteHumain(u8 joueur, u8 lastSelected, u8 phase) {
  s16 currentCard;

  currentCard = lastSelected;
  GDMmettreAJourAffichage(joueur, currentCard, phase);

  SoKeysUpdate();
  while (true) {
    SoKeysUpdate();

    if (SoKeysPressed(SO_KEY_A | SO_KEY_B) && currentCard != NONCARTE)
      return currentCard;
    if (SoKeysPressed(SO_KEY_LEFT | SO_KEY_UP) || SoKeysDown(SO_KEY_L)) {
      do {
	currentCard = SoMathModulus((currentCard == 0 ? NOMBRECARTES : currentCard) - 1, NOMBRECARTES);
      } while (leJeu.lesCartes[currentCard].possedeeParJoueur != joueur);
      // afficherSelectionCarte(joueur, currentCard);
      GDMmettreAJourAffichage(joueur, currentCard, phase);
    }
    else if (SoKeysPressed(SO_KEY_RIGHT | SO_KEY_DOWN) || SoKeysDown(SO_KEY_R)) {
      do {
	currentCard = SoMathModulus((currentCard + 1), NOMBRECARTES);
      } while (leJeu.lesCartes[currentCard].possedeeParJoueur != joueur);
      // afficherSelectionCarte(joueur, currentCard);
      GDMmettreAJourAffichage(joueur, currentCard, phase);
    }
    SoDisplayWaitForVBlankEnd();
    SoDisplayWaitForVBlankStart();
    
  }
}

// Renvoie "true" si aucune carte de "buffer" n'est à NONCARTE.
bool toutesDonnees(u8 * buffer) {
  u8 i;

  for (i = 0 ; i < NOMBRE_CARTES_DONNE ; i++)
    if (buffer[i] == NONCARTE) return false;

  return true;
}

// Cette fonction demande à l'utilisateur de sélectionner
// 3 cartes à donner à son voisin de gauche.
// Très basique pour le moment - printf...
// On suppose qu'on est en mode 4.
void donnerCartesHumain(u8 joueur, u8 * buffer) {
  // const SoImage *font;
  u8 carteCourante, cartePrecedente;
  s16 i, j;

  // font = SoFontGetDefaultFontImage();

  cartePrecedente = NONCARTE;
  carteCourante = NONCARTE;

  // Initialisation.
  for (i = 0 ; i < NOMBRE_CARTES_DONNE ; i ++) {
    buffer[i] = NONCARTE;
  }
  
  i = 0;
  while (true) {
    
    // afficherCartesDonnees(joueur, buffer);
    GDMmettreAJourAffichage(joueur, carteCourante, PHASE_DON);
    carteCourante = selectionCarteHumain(joueur, cartePrecedente, PHASE_DON);
    for(j = 0 ; buffer[j] != carteCourante && j < NOMBRE_CARTES_DONNE;  j++) ;
    if (j < NOMBRE_CARTES_DONNE) {
      buffer[j] = NONCARTE;
    } else {
      buffer[i] = carteCourante;
      if (toutesDonnees(buffer)) {
	GDMmettreAJourAffichage(joueur, carteCourante, PHASE_DON);
	if (! GDMafficherEcranConfirmation(joueur)) {
	  buffer[i] = NONCARTE;
	} else break;
      }
      for (i = 0 ; i < NOMBRE_CARTES_DONNE && buffer[i] != NONCARTE ; i++) ;
    }
    cartePrecedente = carteCourante; 
  }
  
  for (i = 0 ; i < NOMBRE_CARTES_DONNE ; i++) {
    leJeu.lesCartes[buffer[i]].possedeeParJoueur = NONDIST;
  }
}

u8 jouerCarteHumain(u8 joueur) {
  const SoImage *font;
  u8 carte;

  carte = NONDIST;

  font = SoFontGetDefaultFontImage();

  //  SoMode4RendererDrawString(0, 240, 0, lesJoueurs[joueur].nom, font);
  //  SoMode4RendererDrawString(0, 240, 16, "Which card to play ?", font);
  //  SoMode4RendererFlip();

  while (! carteJouable (joueur, carte = selectionCarteHumain(joueur, carte, PHASE_AUTRE)));
  
  return carte;
}
