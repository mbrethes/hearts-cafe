#include "MenuDisplayManagement.h"

u16 miniSpherePlayerIndex;
u16 miniSphereAIRandIndex;
u16 miniSphereAINormlIndex;
u16 menuCurseurIndex;
u16 currentSphereIndex;

u8 lastType;

#define SPHERE_POS_X 171
#define SPHERE_POS_Y 92

#define MINISPHERE_POS_LFTX 6
#define MINISPHERE_POS_Y 124
#define MINISPHERE_OFFSET_X 4

#define SO_REAL_OAM			((u16*)0x7000000)

#define TYPE_OK 255


// Les coordonnées des animations...
#define ANIM_JOHN_X 44
#define ANIM_JOHN_Y 30
#define ANIM_KAY_X  71
#define ANIM_KAY_Y  41
#define ANIM_HCR_X  116
#define ANIM_HCR_Y  52
#define ANIM_ELUF_X 138
#define ANIM_ELUF_Y 20



// Cette fonction change aléatoirement l'attitude des personnages,
// en fonction d'un coefficient donné plus haut.
void MDMchangerAttitudePersonnages() {
  u16 var;
  u8 i;
  bool change = false;

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    
    if (etat[i] == NORMAL) {
      var = SoMathModulus(SoMathRand(), COEFFCHG_NORMAL);
      
      
      if (var == TRUEVAL_NORMAL) {
	change = true;
	etat[i] = ANIME;
      }
    } else {
      var = SoMathModulus(SoMathRand(), COEFFCHG_ANIME);
      
      
      if (var == TRUEVAL_ANIME) {
	change = true;
	etat[i] = NORMAL;
      }
    }
  }

  if (change) {
    if (etat[PLAYER_JOHN] == ANIME) {
      drawBitmapToCoords(& MenuJohnAnimImage, ANIM_JOHN_X, ANIM_JOHN_Y);
    } else {
      drawBitmapToCoords(& MenuJohnOrigImage, ANIM_JOHN_X, ANIM_JOHN_Y);
    }
    if (etat[PLAYER_KAY] == ANIME) {
      drawBitmapToCoords(& MenuKayAnimImage, ANIM_KAY_X, ANIM_KAY_Y);
    } else {
      drawBitmapToCoords(& MenuKayOrigImage, ANIM_KAY_X, ANIM_KAY_Y);
    }
    if (etat[PLAYER_HCR] == ANIME) {
      drawBitmapToCoords(& MenuHCRAnimImage, ANIM_HCR_X, ANIM_HCR_Y);
    } else {
      drawBitmapToCoords(& MenuHCROrigImage, ANIM_HCR_X, ANIM_HCR_Y);
    }
    if (etat[PLAYER_ELUF] == ANIME) {
      drawBitmapToCoords(& MenuElufAnimImage, ANIM_ELUF_X, ANIM_ELUF_Y);
    } else {
      drawBitmapToCoords(& MenuElufOrigImage, ANIM_ELUF_X, ANIM_ELUF_Y);
    }

    SoDisplayWaitForVBlankStart();
    SoMode4RendererFlip();
  }
}

// Initialise l'écran du menu.
void MDMinitialiserEcranMenu() {
  u8 i;

  SoDisplayWaitForVBlankStart();
  SoMode4RendererEnable();

  // On dessine l'image sur les 2 buffers - important, voir plus loin
  SoMode4RendererDrawImage(& GameMenuImage);
  SoDisplayWaitForVBlankStart();
  SoMode4RendererFlip();
  SoMode4RendererDrawImage(& GameMenuImage);

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    etat[i] = NORMAL;
  }

  // BUG indiquer qu'on utilise le mode 1D pour les sprites !

  SO_REG_DISP_CNT |= SO_BIT_6;

  // Phase 0 : charger les sprites utiles.

  SoSpriteMemManagerInitialize ();

  SoSpriteMemManagerSetInBitmappedMode (true);

  // On va charger les 3 petits sprites, ça peut pas faire de mal...
  // Pour les gros, on verra au cas par cas.

  miniSpherePlayerIndex = SoSpriteMemManagerLoad (&MiniSpherePlayerSpriteAnimation);
  miniSphereAIRandIndex = SoSpriteMemManagerLoad (&MiniSphereAIRandSpriteAnimation);
  miniSphereAINormlIndex = SoSpriteMemManagerLoad(&MiniSphereAINormlSpriteAnimation);
  currentSphereIndex = SoSpriteMemManagerLoad(&SpherePlayerSpriteAnimation);

  menuCurseurIndex = SoSpriteMemManagerLoad(&MenuCurseurSpriteAnimation);

  SoPaletteSetPalette (SO_SPRITE_PALETTE, spherePalette, true);
  SoPaletteSetPalette (SO_SCREEN_PALETTE, gameMenuPalette, true);

  SoSpriteManagerEnableSprites ();

  lastType = TYPE_HUMAIN;

}

// Libère la mémoire utilisée dans ce cadre - si tant est.
void MDMlibererEcranMenu() {
  SoPaletteSetBlack(SO_SPRITE_PALETTE, true);
  SoPaletteSetBlack(SO_SCREEN_PALETTE, true);

  SoSpriteMemManagerRelease(menuCurseurIndex);
  SoSpriteMemManagerRelease(currentSphereIndex);
  SoSpriteMemManagerRelease(miniSpherePlayerIndex);
  SoSpriteMemManagerRelease(miniSphereAIRandIndex);
  SoSpriteMemManagerRelease(miniSphereAINormlIndex);
}

// La sphere est stockée à l'emplacement 0 de la OAM
#define SPHERE_OAM 0
// Les minispheres de 1 à 4.
#define MINISPHERE_OAM 1
#define CURSEUR_OAM 5
// Affiche le menu principal de sélection des joueurs.
void MDMafficherMenuSelectionJoueurs(u8 nombreSelectionne, u8 typeJoueur) {
  SoSprite buffer[6];
  u8 i;
  SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;

  // Initialisation.
  for (i = 0 ; i < 6 ; i++) {
    SoSpriteReset(& buffer[i]);
    //SoSpriteDisable(& buffer[i]);
  }

  // Cas général...
  // if (nombreSelectionne == 0) {
  // if (lastType != TYPE_HUMAIN) {
  // SoSpriteMemManagerRelease(currentSphereIndex);
  //    currentSphereIndex = SoSpriteMemManagerLoad(&SpherePlayerSpriteAnimation);
  //    lastType = TYPE_HUMAIN;
  //  }
    
  //  SoSpriteCopyPropertiesFromAnimation(& buffer[SPHERE_OAM], &SpherePlayerSpriteAnimation);
  //  SoSpriteSetAnimationIndex (& buffer[SPHERE_OAM], currentSphereIndex);
    
  //  SoSpriteSetTranslate(& buffer[SPHERE_OAM], SPHERE_POS_X, SPHERE_POS_Y);
    // Active le sprite (il suffit de désactiver le doublesize...)
  //  SoSpriteSetSizeDoubleEnable  (& buffer[SPHERE_OAM], false);
  // } else {
    if (nombreSelectionne < 4) {
      
      if (lastType != typeJoueur) {
	SoSpriteMemManagerRelease(currentSphereIndex);
	switch (typeJoueur) {
	case TYPE_HUMAIN:
	  currentSphereIndex = SoSpriteMemManagerLoad(&SpherePlayerSpriteAnimation);
	  lastType = TYPE_HUMAIN;
	  break;
	case TYPE_IA_ALE:
	  currentSphereIndex = SoSpriteMemManagerLoad(&SphereAIRandSpriteAnimation);
	  lastType = TYPE_IA_ALE;
	  break;
	case TYPE_IA_BAS:
	default:
	  currentSphereIndex = SoSpriteMemManagerLoad(&SphereAINormlSpriteAnimation);
	  lastType = TYPE_IA_BAS;
	}
      }
    } else {
      if (lastType != TYPE_OK) {
	SoSpriteMemManagerRelease(currentSphereIndex);
	currentSphereIndex = SoSpriteMemManagerLoad(&SphereOKSpriteAnimation);
	lastType = TYPE_OK;
      }
    }

    switch (lastType) {
    case TYPE_HUMAIN:
      SoSpriteCopyPropertiesFromAnimation(& buffer[SPHERE_OAM], &SpherePlayerSpriteAnimation);
      break;
    case TYPE_IA_ALE:
      SoSpriteCopyPropertiesFromAnimation(& buffer[SPHERE_OAM], &SphereAIRandSpriteAnimation);
      break;
    case TYPE_IA_BAS:
      SoSpriteCopyPropertiesFromAnimation(& buffer[SPHERE_OAM], &SphereAINormlSpriteAnimation);
      break;
    case TYPE_OK:
      SoSpriteCopyPropertiesFromAnimation(& buffer[SPHERE_OAM], &SphereOKSpriteAnimation);
    }


    SoSpriteSetAnimationIndex (& buffer[SPHERE_OAM], currentSphereIndex);
    
    SoSpriteSetTranslate(& buffer[SPHERE_OAM], SPHERE_POS_X, SPHERE_POS_Y);
    // Active le sprite (il suffit de désactiver le doublesize...)
    SoSpriteSetSizeDoubleEnable  (& buffer[SPHERE_OAM], false);
     
    // On affiche les mini-sprites :)
    for (i = 0 ; i < nombreSelectionne ; i++) {
      switch (lesJoueurs[i].type) {
      case TYPE_HUMAIN:
	SoSpriteCopyPropertiesFromAnimation(& buffer[MINISPHERE_OAM + i], &MiniSpherePlayerSpriteAnimation);
	SoSpriteSetAnimationIndex (& buffer[MINISPHERE_OAM + i], miniSpherePlayerIndex);
	break;
      case TYPE_IA_ALE:
	SoSpriteCopyPropertiesFromAnimation(& buffer[MINISPHERE_OAM + i], &MiniSphereAIRandSpriteAnimation);
	SoSpriteSetAnimationIndex (& buffer[MINISPHERE_OAM + i], miniSphereAIRandIndex);
	break;
      case TYPE_IA_BAS:
      default:
	SoSpriteCopyPropertiesFromAnimation( &buffer[MINISPHERE_OAM + i], &MiniSphereAINormlSpriteAnimation);
	SoSpriteSetAnimationIndex ( &buffer[MINISPHERE_OAM + i], miniSphereAINormlIndex);
	
      }
      SoSpriteSetTranslate( &buffer[MINISPHERE_OAM + i], MINISPHERE_POS_LFTX +i * (SoSpriteGetWidth( &buffer[MINISPHERE_OAM + i]) + MINISPHERE_OFFSET_X) , MINISPHERE_POS_Y);
      // Active le sprite (il suffit de désactiver le doublesize...)
      SoSpriteSetSizeDoubleEnable  (& buffer[SPHERE_OAM], false);
    }
    //}
  
    MDMchangerAttitudePersonnages();

    SoDisplayWaitForVBlankStart();
    SoDMA0Transfer(buffer, OAMSprt, 6 * sizeof(SoSprite) / 2,  SO_DMA_16);
  
}

#define FIRSTCARPOSX 20
#define CAROFFSET    36
#define CHARMIN      ' '
#define CHARMAX      'z'

// Affiche une "fenêtre ASCII" où le joueur pourra sélectionner
// son nom...
// Renvoie "false" si le joueur a annulé (pas de nom sélectionné),
// "true" sinon.
bool MDMselectionnerNomJoueur(char *s, u8 lenmin, u8 lenmax) {
  u8 i, lettreCourante;
  s16 posX, posY;
  bool change = false;
  bool flipper = false;
  char buf[2];

  buf[1] = 0;
  
  // Hardcoded values...

  SoSprite buffer[6];
  SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;

  // Initialisation.
  for (i = 0 ; i < 6 ; i++) {
    SoSpriteReset(& buffer[i]);
    //SoSpriteDisable(& buffer[i]);
  }

  //SoPaletteSetGreyScale(SO_SPRITE_PALETTE, true);
  
  SoMode4RendererDrawImage(& GameMenuGrayImage);
  
  SoMode4RendererDrawString(180, 232, 120, "Name ?", SoFontGetDefaultFontImage());
  SoMode4RendererDrawString(FIRSTCARPOSX, 232, 136, "A", SoFontGetDefaultFontImage());

  SoDisplayWaitForVBlankStart();
  //  SoSpriteManagerDisableSprites();
  SoPaletteSetGreyScale(SO_SCREEN_PALETTE, true);

  SoMode4RendererFlip();

  posY = 132;
  posX = FIRSTCARPOSX - 4;

  lettreCourante = 0;

  SoSpriteCopyPropertiesFromAnimation(& buffer[CURSEUR_OAM], & MenuCurseurSpriteAnimation);

  SoSpriteSetAnimationIndex (& buffer[CURSEUR_OAM], menuCurseurIndex);
  
  SoSpriteSetTranslate(& buffer[CURSEUR_OAM], posX, posY);
  // Active le sprite (il suffit de désactiver le doublesize...)
  SoSpriteSetSizeDoubleEnable  (& buffer[CURSEUR_OAM], false);
  
  SoDisplayWaitForVBlankStart();
  SoDMA0Transfer(buffer, OAMSprt, 6 * sizeof(SoSprite) / 2,  SO_DMA_16);

  for (lettreCourante = 0 ; lettreCourante < lenmax && s[lettreCourante] != 0 ; lettreCourante ++);
  
  if (lettreCourante > 0) lettreCourante --;

  if (lettreCourante < lenmin - 1) 
    s[lettreCourante] = 'A';
  

  change = true;

  SoKeysUpdate();
  while(true) {
    SoKeysUpdate();
    

    
    if (SoKeysPressed(SO_KEY_START)) {
      if (lettreCourante + 1 >= lenmin) {
	s[lettreCourante + 1] = 0;
	change = true;
	SoKeysUpdate();
	// On attend que le joueur relache start...
	while (SoKeysPressed(SO_KEY_START)) {
	  SoDisplayWaitForVBlankStart();
	  SoDisplayWaitForVBlankEnd();
	  SoKeysUpdate();
	}
	break ;
      }
    }
    

    if (SoKeysPressed(SO_KEY_B)) {
      if (lettreCourante == 0) {
	change = false;
	break;
      } else {
	s[lettreCourante] = 0;
	lettreCourante --;
	change = true;
      }
    }

    else if (SoKeysPressed(SO_KEY_A)) {
      if (lettreCourante < lenmax - 1) {
	lettreCourante ++;
	s[lettreCourante] = 'A';
	change = true;
      }
    }

    else if (SoKeysPressed(SO_KEY_UP | SO_KEY_LEFT) || (SoKeysDown(SO_KEY_L) && flipper)) {
      s[lettreCourante] --;
      if (s[lettreCourante] < CHARMIN) {
	s[lettreCourante] = CHARMAX;
      }
      change = true;
    }

    else if( SoKeysPressed(SO_KEY_DOWN | SO_KEY_RIGHT) || (SoKeysDown(SO_KEY_R) && flipper)) {
      s[lettreCourante] ++;
      if (s[lettreCourante] > CHARMAX) {
	s[lettreCourante] = CHARMIN;
      }
      change = true;
    }

    if (change) {
      SoMode4RendererDrawImage(& GameMenuGrayImage);
      SoMode4RendererDrawString(180, 232, 120, "Name ?", SoFontGetDefaultFontImage());

      for (i = 0 ; i <= lettreCourante ; i++) {
	buf[0] = s[i];
	SoMode4RendererDrawString(FIRSTCARPOSX + CAROFFSET * i , 232, 136, buf, SoFontGetDefaultFontImage());
      }
      posX = FIRSTCARPOSX + CAROFFSET * lettreCourante - 4;

      SoSpriteSetTranslate(& buffer[CURSEUR_OAM], posX, posY);
      
      SoDisplayWaitForVBlankStart();
      SoDMA0Transfer(buffer, OAMSprt, 6 * sizeof(SoSprite) / 2,  SO_DMA_16);
      SoMode4RendererFlip();
    }
    SoDisplayWaitForVBlankStart();
    SoDisplayWaitForVBlankEnd();
    flipper = ! flipper;

    change = false;

  }


  // On dessine l'image sur les 2 buffers...
  SoMode4RendererDrawImage(& GameMenuImage);
  SoDisplayWaitForVBlankStart();
  SoPaletteSetPalette(SO_SCREEN_PALETTE, gameMenuPalette, true);
  SoMode4RendererFlip();
  SoMode4RendererDrawImage(& GameMenuImage);

  return change;

}
