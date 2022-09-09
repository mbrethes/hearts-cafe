#include "GameMenu.h"
#include "Mods.h"

const char *lesNoms[] = {
  "J0hn", "Kay", "HCR", "Eluf"
};

// Affiche le menu du jeu.
void GameMenu() {

  bool res;
  u8 i;

  char name[LONGUEUR_NOM];
  s8 nombreSelectionne = 0;
  u8 typeSelectionne = TYPE_HUMAIN;

  MDMinitialiserEcranMenu();

  /*
  afm_install();

  afm_init(&SELPLAYMOD);
  afm_sound_param(0x3E,1);
  */

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (lesJoueurs[i].nom[0] == 0)
      initialiserJoueur(& lesJoueurs[i], TYPE_HUMAIN, lesNoms[i]);
  }

  SoKeysUpdate();
  while (true) {
    SoKeysUpdate();

    if (SoKeysPressed (SO_KEY_L | SO_KEY_LEFT | SO_KEY_UP)) {
      if (typeSelectionne == TYPE_HUMAIN) {
	typeSelectionne = TYPE_IA_BAS;
      } else if (typeSelectionne == TYPE_IA_ALE) {
	typeSelectionne = TYPE_HUMAIN;
      } else {
	typeSelectionne = TYPE_IA_ALE;
      }
    } else if (SoKeysPressed(SO_KEY_R | SO_KEY_RIGHT | SO_KEY_DOWN)) {
      if (typeSelectionne == TYPE_HUMAIN) {
	typeSelectionne = TYPE_IA_ALE;
      } else if (typeSelectionne == TYPE_IA_ALE) {
	typeSelectionne = TYPE_IA_BAS;
      } else {
	typeSelectionne = TYPE_HUMAIN;
      }
    } else if (SoKeysPressed(SO_KEY_B) && nombreSelectionne > 0) {
      nombreSelectionne --;
      typeSelectionne = lesJoueurs[nombreSelectionne].type;
    }
    if (SoKeysPressed(SO_KEY_A) && nombreSelectionne < 4) {
      if (typeSelectionne == TYPE_HUMAIN) {
	for (i = 0 ; i < LONGUEUR_NOM ; i++)
	  name[i] = lesJoueurs[nombreSelectionne].nom[i];
	if (MDMselectionnerNomJoueur(name, LONGUEUR_MINI, LONGUEUR_NOM)) {
	  initialiserJoueur(& lesJoueurs[nombreSelectionne], typeSelectionne, name);
	}
	else nombreSelectionne --;
      } else {
	initialiserJoueur(& lesJoueurs[nombreSelectionne], typeSelectionne, lesNoms[nombreSelectionne]);
      }
      nombreSelectionne ++;
    }
    
    if (SoKeysPressed(SO_KEY_START) && nombreSelectionne >= 4)
      break;
    
    MDMafficherMenuSelectionJoueurs(nombreSelectionne, typeSelectionne);
    
    SoDisplayWaitForVBlankEnd();
    SoDisplayWaitForVBlankStart();
  }

  MDMlibererEcranMenu();

  // afm_deinit();

  initialiserScore();

  // afm_install();

  // afm_init(&MAINGAMEMOD);
  // afm_sound_param(0x3F,1);

  do {

    GDMinitialiserEcranJeu();

    nouvellePartie();

    res = calculerScore();

    GDMlibererEcranJeu();
  } while (res == false);

  // SoIntManagerDisableInterrupt(SO_INTERRUPT_TYPE_VBLANK);

  // afm_deinit();
}

