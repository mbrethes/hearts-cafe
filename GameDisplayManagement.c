#include "GameDisplayManagement.h"

// Nouvelles dÅÈclarations locales...

#define BLEND_1_LEVEL 6
#define BLEND_2_LEVEL 12

#define PALETTE_ROUGE 0
#define PALETTE_NOIRE 1
#define PALETTE_RETOU 2
#define PALETTE_CURSE 3
#define PALETTE_SHOOT 4
#define PALETTE_DA    5
#define PALETTE_MOON  6

#define SO_REAL_OAM			((u16*)0x7000000)

#define SPRITE_OFFSET_DV 0
#define SPRITE_OFFSET_G  13
#define SPRITE_OFFSET_M  26
#define SPRITE_OFFSET_D  39
// Le curseur est stockÅÈ Å‡ la "position" 52.
#define CURSEUR_SPR_NUM  52
// L'offset des 4 cartes en cours de jeu.
#define SPRITE_OFF_CSET  53
// L'offset des 3 sprites "shoot da moon"
#define SHDAMOON_OFF 57

// Offset de dÅÈmarrage des affichages de cartes
#define POS_X_DV  8
#define POS_Y_DV  96
#define OFFSET_DV 16
#define POS_X_M   88
#define POS_Y_M   50
#define OFFSET_M  4
#define POS_X_G   0
#define POS_Y_G   52
#define OFFSET_G  4
#define POS_X_D   176
#define POS_Y_D   52
#define OFFSET_D  4

#define CSET_X    160
#define CSET_Y    4
#define CSET_OFF  16

// Et du shdamoon
#define SHDAMOON_Y_MIN 29
#define SHDAMOON_Y_OFF 3

// Defines pour les BKGs
#define TILEBASE  1
#define BKG0_MAP  0
#define BKG1_MAP  1
#define BKG2_MAP  2
#define BKG3_MAP  3

#define Y_HAUT_HUMAIN  0
#define Y_HAUT_MACHINE 32

#define BKG3_MIN_Y_INDEX 7

static u8 joueurSurLeDevant;

static u16 curseurIndex;
static u16 curseurNonIndex;
static u16 curseurOKIndex;
static u16 carteRetourneeIndex;

#define MAP_SX 30
#define MAP_SY 10

static u8 lastDrawn;
/*
// Cette fonction change alÅÈatoirement l'attitude des personnages,
// en fonction d'un coefficient donnÅÈ plus haut.
void GDMchangerAttitudePersonnages() {
  u16 var;
  u8 i, j;
  bool change[NOMBRE_JOUEURS];

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) 
    change[i] = false;

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    
    if (etat[i] == NORMAL) {
      var = SoMathModulus(SoMathRand(), COEFFCHG_NORMAL);
      
      
      if (var == TRUEVAL_NORMAL) {
	change[i] = true;
	etat[i] = ANIME;
      }
    } else {
      var = SoMathModulus(SoMathRand(), COEFFCHG_ANIME);
      if (var == TRUEVAL_ANIME) {
	change[i] = true;
	etat[i] = NORMAL;
      }
    }
  }

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (change[i])
      switch(i) {
      case PLAYER_JOHN:
	for (j = 0 ; j < JOHN_NBTILES ; j++) {
	  swapTiles(OFFSET_FIRST_PERSO + JOHN_POS_Y * 40 + JOHN_POS_X + j, OFFSET_FIRST_SUPP + j, 1);
	}
	break;
      case PLAYER_KAY:
	for (j = 0 ; j < KAY_NBTILES ; j++) {
	  swapTiles(OFFSET_FIRST_PERSO + KAY_POS_Y * 40 + KAY_POS_X + j, OFFSET_FIRST_SUPP + j + JOHN_NBTILES, 1);
	}
	break;
      case PLAYER_HCR:
	for (j = 0 ; j < HCR_NBTILES ; j++) {
	  swapTiles(OFFSET_FIRST_PERSO + HCR_POS_Y * 40 + HCR_POS_X + j, OFFSET_FIRST_SUPP + j + JOHN_NBTILES + KAY_NBTILES, 1);
	}
	break;
      case PLAYER_ELUF:
	for (j = 0 ; j < ELUF_NBTILES ; j++) {
	  swapTiles(OFFSET_FIRST_PERSO + ELUF_POS_Y * 40 + ELUF_POS_X + j, OFFSET_FIRST_SUPP + j + JOHN_NBTILES + KAY_NBTILES + HCR_NBTILES, 1);
	}
      }
  }
}
*/

// Cette fonction met Å‡ jour la "map" du BKG 3
// si le joueur courant est humain, bien entendu.
// On peut forcer la mise Å‡ jour - premier affichage par ex.
void GDMmettreAJourBKG3(u8 joueurCourant, bool force, u8 offY) {
  if ((lesJoueurs[joueurCourant].type == TYPE_HUMAIN && joueurCourant != lastDrawn) || force == true) {
    SoBkgMap tmpMap;
    u16 mapData[MAP_SX * MAP_SY];
    
    u8 i, x, y;
    
    lastDrawn = joueurCourant;
    
    for (i = 0 ; i < NOMBRE_JOUEURS - 1 ; i++) {
      for (x = 0 ; x < MAP_SX / 3 ; x++) {
	for (y = 0 ; y < MAP_SY ; y++) {
	  mapData[y*(MAP_SX) + (x + i*MAP_SY)] = OFFSET_FIRST_PERSO + (y * 40) + x + SoMathModulus(i + joueurCourant + 1, NOMBRE_JOUEURS) * 10;
	}
      }
    }

    tmpMap.m_16Colors = false;
    tmpMap.m_SizeX = MAP_SX;
    tmpMap.m_SizeY = MAP_SY;
    tmpMap.m_Data  = (u16 *) mapData;

    SoDisplayWaitForVBlankStart();
    SoBkgWriteBlock  (3, 0, BKG3_MIN_Y_INDEX, SoBkgMapGetNumCols(& tmpMap), SoBkgMapGetNumRows(& tmpMap), SoBkgMapGetNumCols(& tmpMap), SoBkgMapGetData(& tmpMap));
    SoBkgWriteBlock(3, 0, BKG3_MIN_Y_INDEX + MAP_SY, SoBkgMapGetNumCols(& BG3Map), SoBkgMapGetNumRows(& BG3Map), SoBkgMapGetNumCols(& BG3Map), SoBkgMapGetData(& BG3Map));
  }
    
  SoBkgSetOffset (3, 0, 72 - offY);
}

// Nouvelles fonctions (et finales ;-) )

// Cette fonction initialise l'ÅÈcran de jeu, en appelant le mode 0
// et en mettant Å‡ jour les sprites. Elle ne fait aucune assertion
// concernant l'ÅÈtat prÅÈcÅÈdent de l'ÅÈcran, toutes les donnÅÈes de
// l'ÅÈtat prÅÈcÅÈdent seront donc perdues (au niveau hardware).

void GDMinitialiserEcranJeu() {
  u8 i;
  SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;
  
  // Phase 1. Passer en mode 0.

  SoDisplaySetMode(0);

  // BUG indiquer qu'on utilise le mode 1D pour les sprites !

  SO_REG_DISP_CNT |= SO_BIT_6;

  // Phase 2. 

  // 2.1. Activer et initialiser tous les arriÅËre-plans qu'on utilise.
  
  SoBkgSetup(0, SO_BKG_PRIORITY_0 | SO_BKG_CHARBASE(TILEBASE) | SO_BKG_MOSAIC_DISABLE |  SO_BKG_SCRBASE(BKG0_MAP) | SO_BKG_TEXTSIZE_256x256 | SO_BKG_CLRMODE_256);
  SoBkgSetup(1, SO_BKG_PRIORITY_1 | SO_BKG_CHARBASE(TILEBASE) | SO_BKG_MOSAIC_DISABLE |  SO_BKG_SCRBASE(BKG1_MAP) | SO_BKG_TEXTSIZE_256x256 | SO_BKG_CLRMODE_256);
  SoBkgSetup(2, SO_BKG_PRIORITY_2 | SO_BKG_CHARBASE(TILEBASE) | SO_BKG_MOSAIC_DISABLE |  SO_BKG_SCRBASE(BKG2_MAP) | SO_BKG_TEXTSIZE_256x256 | SO_BKG_CLRMODE_256);

  SoBkgSetup(3, SO_BKG_PRIORITY_3 | SO_BKG_CHARBASE(TILEBASE) | SO_BKG_MOSAIC_DISABLE |  SO_BKG_SCRBASE(BKG3_MAP) | SO_BKG_TEXTSIZE_256x256 | SO_BKG_CLRMODE_256);

  SoBkgEnable(3, false);
  // 2.2. Tous pointent sur le cotÅÈ haut-gauche...

  for (i = 0 ; i < 3 ; i++) {
    SoBkgSetOffset(i, 0, 0);
  }
  

  // DÅÈfinition supplÅÈmentaire pour l'alpha-blending...
  SoWindow0OutsideEffectsEnable( true );
  SoWindow0InsideEffectsEnable( true );
  SoEffectsSetBlend(BLEND_1_LEVEL, BLEND_2_LEVEL);
  SoEffectsSetMode  (SO_EFFECTS_MODE_BLEND, SO_EFFECTS_TARGET1_BG1 | SO_EFFECTS_TARGET1_BG2, SO_EFFECTS_TARGET2_ALL);
  // 2.3. Charger le tileset et les maps

  SoTileSetBkgLoad(& MainGameTilesTileSet, TILEBASE, 0);

  SoBkgWriteBlock  (1, 0, 0, SoBkgMapGetNumCols(& BG1Map), SoBkgMapGetNumRows(& BG1Map), SoBkgMapGetNumCols(& BG1Map), SoBkgMapGetData(& BG1Map));
  SoBkgWriteBlock  (2, 0, 0, SoBkgMapGetNumCols(& BG2Map), SoBkgMapGetNumRows(& BG2Map), SoBkgMapGetNumCols(& BG2Map), SoBkgMapGetData(& BG2Map)); 

  // PremiÅËre mise Å‡ jour de l'affichage du BKG 3...
  lastDrawn = 1;
  GDMmettreAJourBKG3(0, true, 72);

  SoBkgEnable(0, true);
  SoBkgEnable(1, false);
  SoBkgEnable(2, true);
  SoBkgEnable(3, true);
  // Effacer les sprites.

  // La mÅÈmoire OAM ne peut ÅÍtre accÅÈdÅÈe que pendant le VBlank.
  SoDisplayWaitForVBlankStart ();
  for (i = 0 ; i < 128 ; i++)
    SoSpriteDisable(& OAMSprt[i]);

  SoSpriteManagerEnableSprites();

  // Phase 3. DÅÈmarrer le systÅËme de gestion mÅÈmoire des sprites.

  // Bug corrigÅÈ dans SGADE, Å‡ ce propos...
  SoSpriteMemManagerSetInBitmappedMode  (false); 
  SoSpriteMemManagerInitialize();
   
  // Phase 4. Euuuuh... CrÅÈer la palette pour les sprites et les bkg ?

  SoPaletteSetBlack(SO_SPRITE_PALETTE, true);
  SoPaletteSetPalette(SO_SCREEN_PALETTE, mainGameTilesPalette, true);

  // 16 couleurs...
  SoPaletteSetPalette(SO_SPRITE_PALETTE, rougePalette, false);
  SoPaletteSetPalette(& SO_SPRITE_PALETTE[16], noirPalette, false);
  SoPaletteSetPalette(& SO_SPRITE_PALETTE[32], retourneePalette, false);
  SoPaletteSetPalette(& SO_SPRITE_PALETTE[48], curseurPalette, false);
  SoPaletteSetPalette(& SO_SPRITE_PALETTE[64], SHOOTPalette, false);
  SoPaletteSetPalette(& SO_SPRITE_PALETTE[80], DAPalette, false);
  SoPaletteSetPalette(& SO_SPRITE_PALETTE[96], MOONPalette, false);

  // Phase 5. DÅÈterminer quel sera le premier joueur (humain) Å‡ ÅÍtre sur le
  // devant (il y a au moins 1 humain qui joue)

  i = 0;

  while ( i < NOMBRE_JOUEURS && lesJoueurs[i].type != TYPE_HUMAIN) i++;

  joueurSurLeDevant = i;

  // Phase 6. Charger les premiers sprites.

  curseurIndex = SoSpriteMemManagerLoad(& CurseurSpriteAnimation);
  curseurNonIndex = SoSpriteMemManagerLoad(& CurseurNonSpriteAnimation);
  curseurOKIndex = SoSpriteMemManagerLoad(& CurseurOKSpriteAnimation);
  carteRetourneeIndex = SoSpriteMemManagerLoad( & RetourneeSpriteAnimation);

  // Fini !

}

// Renvoie "true" si la carte donnÅÈe est Å‡ jour dans la OAM ram,
// "false" sinon. Il s'agit de cartes complÅËtes, pas de dos.
bool estAJourDansOAM(u8 carte) {
  return ! (leJeu.lesCartes[carte].data == NONINIT || leJeu.lesCartes[carte].data == carteRetourneeIndex);
}

// Charge les donnÅÈes de la carte courante dans la mÅÈmoire OAM.
void chargerCarteDansOAM(u8 carte) {
  switch (leJeu.lesCartes[carte].couleur) {
  case CARREAU:
    leJeu.lesCartes[carte].data = SoSpriteMemManagerLoad( & CarreauSpriteAnimation[leJeu.lesCartes[carte].force]);
    break;
  case COEUR:
    leJeu.lesCartes[carte].data = SoSpriteMemManagerLoad( & CoeurSpriteAnimation[leJeu.lesCartes[carte].force]);
    break;
  case PIQUE:
    leJeu.lesCartes[carte].data = SoSpriteMemManagerLoad( & PiqueSpriteAnimation[leJeu.lesCartes[carte].force]);
    break;
  case TREFLE:
    leJeu.lesCartes[carte].data = SoSpriteMemManagerLoad( & TrefleSpriteAnimation[leJeu.lesCartes[carte].force]);
  }
}

// Met Å‡ jour les propriÅÈtÅÈs de la carte courante dans le sprite courant.
void metAJourPropriCarteOAM(u8 carte, SoSprite * sp) {
  switch (leJeu.lesCartes[carte].couleur) {
  case CARREAU:
    SoSpriteCopyPropertiesFromAnimation(sp, & CarreauSpriteAnimation[leJeu.lesCartes[carte].force]);
    SoSpriteSetPalette(sp, PALETTE_ROUGE, SO_BKG_PRIORITY_2 );
    break;
  case COEUR:
    SoSpriteCopyPropertiesFromAnimation(sp, & CoeurSpriteAnimation[leJeu.lesCartes[carte].force]);
    SoSpriteSetPalette(sp, PALETTE_ROUGE, SO_BKG_PRIORITY_2 );
    break;
  case PIQUE:
    SoSpriteCopyPropertiesFromAnimation(sp, & PiqueSpriteAnimation[leJeu.lesCartes[carte].force]);
    SoSpriteSetPalette(sp, PALETTE_NOIRE, SO_BKG_PRIORITY_2 );
    break;
  case TREFLE:
    SoSpriteCopyPropertiesFromAnimation(sp, & TrefleSpriteAnimation[leJeu.lesCartes[carte].force]);
    SoSpriteSetPalette(sp, PALETTE_NOIRE, SO_BKG_PRIORITY_2 );
  }
}

// Cette procÅÈdure met Å‡ jour sp pour l'affichage. X_left et Y_left
// correspondent aux coordonnÅÈes du sprite.
void showSprite(SoSprite *sp, u16 index, s32 X_left, s32 Y_left) {
  SoSpriteSetAnimationIndex(sp, index);
  //SoSpriteSetTranslate(sp, X_left + SoSpriteGetWidth(sp) / 2, Y_left + SoSpriteGetHeight(sp) / 2);
  SoSpriteSetTranslate(sp, X_left, Y_left);
  // Active le sprite (il suffit de dÅÈsactiver le doublesize...)
  SoSpriteSetSizeDoubleEnable  (sp, false);
}

// Cette fonction met Å‡ jour le haut de l'affichage (i.e. le bkg 2 et les
// cartes qui ont ÅÈtÅÈ jouÅÈes). Un offset est donnÅÈ pour indiquer la distance
// a partir du haut de l'ÅÈcran Å‡ laquelle doit ÅÍtre affichÅÈ le schmilblick.
// varie de -32 Å‡ 0.
void GDMmiseAJourAffichageHaut(SoSprite *ShadowSprt, s16 offset) {
  u8 i;

  SoBkgSetOffset(2, 0, - offset);

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (carteJoueeSurLeTour[i] != NONCARTE) {
      // Carte Å‡ jour dans la OAMram ?
      if (! estAJourDansOAM(carteJoueeSurLeTour[i])) {
	chargerCarteDansOAM(carteJoueeSurLeTour[i]);
      }

      // SoSpriteReset(& ShadowSprt[SPRITE_OFF_CSET + NOMBRE_JOUEURS - i - 1]);
      // metAJourPropriCarteOAM(carteJoueeSurLeTour[i], & ShadowSprt[SPRITE_OFF_CSET + NOMBRE_JOUEURS - i - 1]);
      switch (i) {
      case 0:
	SoSpriteReset(& ShadowSprt[SPRITE_OFF_CSET + 1]);
	metAJourPropriCarteOAM(carteJoueeSurLeTour[i], & ShadowSprt[SPRITE_OFF_CSET + 1]);
	showSprite(& ShadowSprt[SPRITE_OFF_CSET + 1], leJeu.lesCartes[carteJoueeSurLeTour[i]].data, 2 * CSET_OFF + CSET_X, CSET_Y + offset + 4);
	break;
      case 1:
	SoSpriteReset(& ShadowSprt[SPRITE_OFF_CSET + 3]);
	metAJourPropriCarteOAM(carteJoueeSurLeTour[i], & ShadowSprt[SPRITE_OFF_CSET + 3]);
	showSprite(& ShadowSprt[SPRITE_OFF_CSET + 3], leJeu.lesCartes[carteJoueeSurLeTour[i]].data, 0 * CSET_OFF + CSET_X, CSET_Y + offset + 0);
	break;
      case 2:
	SoSpriteReset(& ShadowSprt[SPRITE_OFF_CSET + 2]);
	metAJourPropriCarteOAM(carteJoueeSurLeTour[i], & ShadowSprt[SPRITE_OFF_CSET + 2]);
	showSprite(& ShadowSprt[SPRITE_OFF_CSET + 2], leJeu.lesCartes[carteJoueeSurLeTour[i]].data, 1 * CSET_OFF + CSET_X, CSET_Y + offset - 4);
	break;
      case 3:
	SoSpriteReset(& ShadowSprt[SPRITE_OFF_CSET + 0]);
	metAJourPropriCarteOAM(carteJoueeSurLeTour[i], & ShadowSprt[SPRITE_OFF_CSET + 0]);
	showSprite(& ShadowSprt[SPRITE_OFF_CSET + 0], leJeu.lesCartes[carteJoueeSurLeTour[i]].data, 3 * CSET_OFF + CSET_X, CSET_Y + offset + 0);
      }
      // showSprite(& ShadowSprt[SPRITE_OFF_CSET + NOMBRE_JOUEURS - i - 1], leJeu.lesCartes[carteJoueeSurLeTour[i]].data, i * CSET_OFF + CSET_X, CSET_Y + offset);
    }
  }
}

// Cette fonction met Å‡ jour le bas de l'affichage.
// l'offset peut varier de 0 Å‡ + 64.
void GDMmiseAJourAffichageBas(SoSprite *ShadowSprt, s16 offset, u8 carte_selectionnee, u8 joueurCourant, u8 phase) {
  u8 joueurG, joueurM, joueurD;
  u8 i, j;
  s8 offY;
  u8 nbCJoueurDv, nbCJoueurG, nbCJoueurM, nbCJoueurD;

  nbCJoueurDv = 0;
  nbCJoueurG  = 0;
  nbCJoueurM  = 0;
  nbCJoueurD  = 0;
  
  // On dÅÈtermine qui sont les joueurs gauche, milieu, et droit
  // en fonction du joueur courant sur le devant.
  joueurG = SoMathModulus(joueurSurLeDevant + 1, NOMBRE_JOUEURS);
  joueurM = SoMathModulus(joueurSurLeDevant + 2, NOMBRE_JOUEURS);
  joueurD = SoMathModulus(joueurSurLeDevant + 3, NOMBRE_JOUEURS);

  // Les 52 premiers sprites sont rÅÈservÅÈes aux joueurs : 
  // 0-12 pour le joueur de devant,
  // 13-25 pour celui de gauche,
  // 26-38 pour celui du milieu,
  // 39-51 pour celui de droite.
  
  GDMmettreAJourBKG3(joueurCourant, false, offset);

  for (i = 0 ; i < NOMBRECARTES ; i++) {
    // en fonction des cartes...

    offY = 0;
    for (j = 0 ; j < NOMBRE_CARTES_DONNE * NOMBRE_JOUEURS ; j++) {
      if (carteDonneeAuDebut[j] == i) {
	offY = -8;
	break;
      }
    }

    if (leJeu.lesCartes[i].possedeeParJoueur == joueurSurLeDevant) {
      
      // On charge ÅÈventuellement la carte donnÅÈe dans la mÅÈmoire OAM.
      if (! estAJourDansOAM(i)) {
	chargerCarteDansOAM(i);
      }
      // Dans tous les cas :
      
      SoSpriteReset(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurDv + SPRITE_OFFSET_DV]);
      
      metAJourPropriCarteOAM(i, & ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurDv + SPRITE_OFFSET_DV]);

      showSprite(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurDv + SPRITE_OFFSET_DV], leJeu.lesCartes[i].data, nbCJoueurDv * OFFSET_DV + POS_X_DV, POS_Y_DV + offY + offset);
      
      

      // Si le curseur est sur la carte courante :
      if (i == carte_selectionnee) {
	SoSpriteReset(& ShadowSprt[CURSEUR_SPR_NUM]);

	if (carteJouable(joueurCourant, i) || phase == PHASE_DON) {

	  SoSpriteCopyPropertiesFromAnimation(& ShadowSprt[CURSEUR_SPR_NUM], & CurseurSpriteAnimation);
	  SoSpriteSetPalette(& ShadowSprt[CURSEUR_SPR_NUM], PALETTE_CURSE, SO_BKG_PRIORITY_2 );

	  showSprite(& ShadowSprt[CURSEUR_SPR_NUM], curseurIndex, nbCJoueurDv * OFFSET_DV + POS_X_DV, POS_Y_DV + offY - 20 + offset);
	} else {
	  SoSpriteCopyPropertiesFromAnimation(& ShadowSprt[CURSEUR_SPR_NUM], & CurseurNonSpriteAnimation);
	  SoSpriteSetPalette(& ShadowSprt[CURSEUR_SPR_NUM], PALETTE_CURSE, SO_BKG_PRIORITY_2 );

	  showSprite(& ShadowSprt[CURSEUR_SPR_NUM], curseurNonIndex, nbCJoueurDv * OFFSET_DV + POS_X_DV, POS_Y_DV + offY - 20 + offset);
	}
      }

      nbCJoueurDv ++;

      // Fini !
    } else {

      if (leJeu.lesCartes[i].possedeeParJoueur == joueurG || leJeu.lesCartes[i].possedeeParJoueur == joueurM || leJeu.lesCartes[i].possedeeParJoueur == joueurD) {
	// Dans tous les cas, vÅÈrifier si le sprite est dÅÈjÅ‡ dans la OAM.
	// Si il y est (on ne sait jamais...), libÅÈrer l'espace qu'il occupe.

	if (leJeu.lesCartes[i].data != NONINIT && leJeu.lesCartes[i].data != carteRetourneeIndex) {
	  SoSpriteMemManagerRelease(leJeu.lesCartes[i].data);
	  leJeu.lesCartes[i].data = carteRetourneeIndex;
	}
	
	if (leJeu.lesCartes[i].possedeeParJoueur == joueurG) {
	  SoSpriteReset(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurG + SPRITE_OFFSET_G]);
	  SoSpriteCopyPropertiesFromAnimation(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurG + SPRITE_OFFSET_G], & RetourneeSpriteAnimation);
	  SoSpriteSetPalette(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurG + SPRITE_OFFSET_G], PALETTE_RETOU, SO_BKG_PRIORITY_3 );

	  showSprite(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurG + SPRITE_OFFSET_G], carteRetourneeIndex, nbCJoueurG * OFFSET_G + POS_X_G, POS_Y_G + offY + offset);
	  
	  nbCJoueurG ++;
	} else if (leJeu.lesCartes[i].possedeeParJoueur == joueurM) {
	  SoSpriteReset(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurM + SPRITE_OFFSET_M]);
	  SoSpriteCopyPropertiesFromAnimation(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurM + SPRITE_OFFSET_M], & RetourneeSpriteAnimation);
	  SoSpriteSetPalette(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurM + SPRITE_OFFSET_M], PALETTE_RETOU, SO_BKG_PRIORITY_3 );

	  showSprite(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurM + SPRITE_OFFSET_M], carteRetourneeIndex, nbCJoueurM * OFFSET_M + POS_X_M, POS_Y_M + offY + offset);
	  
	  nbCJoueurM ++;
	} else if (leJeu.lesCartes[i].possedeeParJoueur == joueurD) {
	  SoSpriteReset(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurD + SPRITE_OFFSET_D]);
	  SoSpriteCopyPropertiesFromAnimation(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurD + SPRITE_OFFSET_D], & RetourneeSpriteAnimation);
	  SoSpriteSetPalette(& ShadowSprt[ NOMBRECARTES / NOMBRE_JOUEURS - 1- nbCJoueurD + SPRITE_OFFSET_D], PALETTE_RETOU, SO_BKG_PRIORITY_3 );

	  showSprite(& ShadowSprt[NOMBRECARTES / NOMBRE_JOUEURS - 1 - nbCJoueurD + SPRITE_OFFSET_D], carteRetourneeIndex, nbCJoueurD * OFFSET_D + POS_X_D, POS_Y_D + offY + offset);
	
	  nbCJoueurD ++;
	}
      } else {
	// Cas gÅÈnÅÈral : on libÅËre... Pour le moment !
	SoSpriteMemManagerRelease(leJeu.lesCartes[i].data);
	leJeu.lesCartes[i].data = NONINIT;
      }
    }
  }
}

// Cette fonction est littÅÈralement la plus importante. Elle met Å‡ jour
// l'affichage en fonction de beaucoup de paramÅËtres. Elle dÅÈtermine toute
// seule si on est en phase de don de cartes ou pas, et elle affiche en
// consÅÈquence les cartes. Elle s'occupe ÅÈgalement de la gestion mÅÈmoire
// des cartes, sachant que :
// les 13 premiers sprites correspondent aux X cartes du joueur
// qui se trouve sur le devant.
// les 13*3 sprites qui suivent aux cartes des 3 autres joueurs, respectivement
// gauche (joueur suivant), milieu, droite.
// les 4 suivants aux cartes jouÅÈes (pas obligatoirement toutes Å‡ la fois).
// Le "phase" reprÅÈsente la phase de jeu... Fin de tour, dÅÈbut de tour, etc.
// voir le header.

void GDMmettreAJourAffichage(u8 joueur_courant, u8 carte_selectionnee, u8 phase) {
  u8 i;
  
  // On utilise un shadow, histoire que ÅÁa aille plus vite.
  SoSprite ShadowSprt[128];
  SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;

  for (i = 0 ; i < 128 ; i++) {
    SoSpriteReset(& ShadowSprt[i]);
    SoSpriteDisable(& ShadowSprt[i]);
  }

  // Juste pour ralentir l'action...
  // SoDisplayWaitForVBlankStart();
  // SoDisplayWaitForVBlankEnd();
  
  // Phase 1. Si le joueur courant est humain... Il passe sur le devant.
  if (lesJoueurs[joueur_courant].type == TYPE_HUMAIN) {
    joueurSurLeDevant = joueur_courant;
  }

  // Phase encore encore aprÅËs : dÅÈfinir quelles cartes sont
  // affichÅÈes comme ÅÈtant en cours de jeu...
  // Effet spÅÈcial si le joueur Å‡ venir n'est pas un ordi...

  if (lesJoueurs[joueur_courant].type == TYPE_HUMAIN) {
    switch (phase) {
    case PHASE_FIN_TOUR:
      // On ne descend que si le joueur courant est humain.
      for (i = 0 ; i < 37 ; i++) {
	if (i < 33) GDMmiseAJourAffichageHaut(ShadowSprt, - i);
	GDMmiseAJourAffichageBas(ShadowSprt, i * 2, carte_selectionnee, joueur_courant, phase);
	SoDisplayWaitForVBlankStart ();
	SoDMA3Transfer (ShadowSprt, OAMSprt, 128 * sizeof(SoSprite) / 4,  SO_DMA_32);
	//SoDisplayWaitForVBlankEnd();
      }
      break;
    case PHASE_DEBUT_TOUR:
      // On ne remonte que si le joueur courant est humain.
      GDMafficherEcranAttente(joueur_courant);
      for (i = 0 ; i < 33 ; i++) {
	if (i < 33) GDMmiseAJourAffichageHaut(ShadowSprt, - (32 - i));
	GDMmiseAJourAffichageBas(ShadowSprt, 72 - (i * 2), carte_selectionnee, joueur_courant, phase);
	SoDisplayWaitForVBlankStart ();
	SoDMA3Transfer (ShadowSprt, OAMSprt, 128 * sizeof(SoSprite) / 4,  SO_DMA_32);
	//SoDisplayWaitForVBlankEnd();
      }
      break;
    default:
      GDMmiseAJourAffichageHaut(ShadowSprt, 0);
      GDMmiseAJourAffichageBas(ShadowSprt, 0, carte_selectionnee, joueur_courant, phase);
      SoDisplayWaitForVBlankStart ();
      SoDMA3Transfer (ShadowSprt, OAMSprt, 128 * sizeof(SoSprite) / 4,  SO_DMA_32);
    }
    // Dans le cas "ordinateur", les donnÅÈes sont affichÅÈes en traction max...
  } else {
    GDMmiseAJourAffichageHaut(ShadowSprt, - 32);
    GDMmiseAJourAffichageBas(ShadowSprt, 72, carte_selectionnee, joueur_courant, phase);
    SoDisplayWaitForVBlankStart ();
    SoDMA3Transfer (ShadowSprt, OAMSprt, 128 * sizeof(SoSprite) / 4,  SO_DMA_32);
  }
  
  // Et pour finir, on copie notre shadow oam dans la vraie :)
  // SoDisplayWaitForVBlankStart ();
  // SoDMA3Transfer (ShadowSprt, OAMSprt, 128 * sizeof(SoSprite) / 4,  SO_DMA_32);

  // Ici, on met l'attitude de nos persos Å‡ jour...
  // GDMchangerAttitudePersonnages();
}


void GDMafficherScore(bool shdamoon) {
  u8 i;
  char print[5];
  print[4] = 0;
  print[0] = ':';
  bool finPartie = false;
  u8 scoreMini = 200;

  SoEffectsSetMode  (SO_EFFECTS_MODE_BLEND, SO_EFFECTS_TARGET1_BG2, SO_EFFECTS_TARGET2_ALL);

  // On affiche le fond de l'ÅÈcran d'attente.
  SoBkgEnable(1, true);

  if (shdamoon) {
    GDManimationShootDaMoon();
  }

  for (i = 0 ; i < NOMBRE_JOUEURS; i++) {
    if (score[i]< scoreMini) scoreMini = score[i];
    if (score[i] >=100) finPartie = true;
  } 

  // Phase 0 (test) : afficher le nom du joueur courant.
  if (! finPartie) writeStringToBkg("Match finished.", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  else writeStringToBkg("END OF GAME !  ", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);

  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    writeStringToBkg(lesJoueurs[i].nom, 0, 7, 8 + (i * 2), FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
    u2str(score[i], &print[1], 3, ' ');
    writeStringToBkg(print, 0, 8 + LONGUEUR_NOM, 8 + (i * 2), FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
    if (score[i] == scoreMini && finPartie) {
      writeStringToBkg("winner", 0, 8 + LONGUEUR_NOM + 5, 8 + (i*2), FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
    }
  }
  
  SoKeysUpdate();
  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysPressed(SO_KEY_START));

  // Double attente...

  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysReleased(SO_KEY_START));


  // On efface tout...
  writeStringToBkg("               ", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    writeStringToBkg("          ", 0, 6, 7 +(i * 2), FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
    writeStringToBkg("    ", 0, 7 + LONGUEUR_NOM, 7 +(i * 2), FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  }

  SoBkgEnable(1, false);

  SoEffectsSetMode  (SO_EFFECTS_MODE_BLEND, SO_EFFECTS_TARGET1_BG1 | SO_EFFECTS_TARGET1_BG2, SO_EFFECTS_TARGET2_ALL);
  
}

// Cette fonction libÅËre l'ÅÈcran de jeu pour permettre, par exemple, une
// nouvelle partie...
void GDMlibererEcranJeu() {
  u8 i;

  SoSpriteManagerDisableSprites ();

  SoPaletteSetBlack(SO_SPRITE_PALETTE, true);
  SoPaletteSetBlack(SO_SCREEN_PALETTE, true);


  for (i = 0 ; i < NOMBRECARTES; i++) {
    if (estAJourDansOAM(i)) {
      SoSpriteMemManagerRelease(leJeu.lesCartes[i].data);
    }
    leJeu.lesCartes[i].data = NONINIT;
  }

  SoSpriteMemManagerRelease(curseurOKIndex);

  SoSpriteMemManagerRelease(curseurNonIndex);

  SoSpriteMemManagerRelease(curseurIndex);

  SoSpriteMemManagerRelease(carteRetourneeIndex);

  SoEffectsSetMode  (SO_EFFECTS_MODE_NONE, SO_EFFECTS_TARGET1_ALL, SO_EFFECTS_TARGET2_ALL);
  
}

// Cette fonction affiche un ÅÈcran d'attente, demandant au joueur courant
// de patienter.
void GDMafficherEcranAttente(u8 joueur_courant) {

  // On affiche le fond de l'ÅÈcran d'attente.
  SoBkgEnable(1, true);

  // Phase 0 (test) : afficher le nom du joueur courant.
  writeStringToBkg("Player", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg(lesJoueurs[joueur_courant].nom, 0, 13, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg("It is YOUR turn...", 0, 6, 7, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  
  SoKeysUpdate();
  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysPressed(SO_KEY_START));
  
  // Double attente...

  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysReleased(SO_KEY_START));


  
  SoBkgEnable(1, false);

  writeStringToBkg("      ", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg("          ", 0, 13, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg("                  ", 0, 6, 7, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);

}

// Affiche un ÅÈcran rÅÈcapitulatif du pli, avec : le nom du joueur gagnant, 
// et les cartes qui viennent d'ÅÍtre remportÅÈes (copie de sprites...).
// prÅÈsupposÅÈ : les 4 cartes sont toujours chargÅÈes dans la VRAM.
void GDMafficherEcranRecapitulatifPli(u8 joueur_gagnant, u8 premier_joueur) {
  u8 i;
  // s8 off;

  SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;
  

  SoBkgEnable(1, true);

  // Phase 0 (test) : afficher le nom du joueur courant.
  writeStringToBkg("Player", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg(lesJoueurs[joueur_gagnant].nom, 0, 13, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  if (lesJoueurs[joueur_gagnant].type == TYPE_HUMAIN)
    writeStringToBkg("YOU won the trick !", 0, 6, 7, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  else 
    writeStringToBkg("won the trick.     ", 0, 6, 7, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);

  SoDisplayWaitForVBlankStart();
  for (i = 0 ; i < NOMBRE_JOUEURS ; i++) {
    if (carteJoueeSurLeTour[i] != NONCARTE) {
      // Carte Å‡ jour dans la OAMram ?
      // if (! estAJourDansOAM(carteJoueeSurLeTour[i])) {
      //chargerCarteDansOAM(carteJoueeSurLeTour[i]);
      // }

      // les cartes sont inversÅÈes Å‡ l'ÅÈcran :-p
      // if ((NOMBRE_JOUEURS - i - 1) == premier_joueur) off = - 4;
      // else off = 0;
      
      // SoSpriteReset(& ShadowSprt[i]);
      // metAJourPropriCarteOAM(carteJoueeSurLeTour[i], & ShadowSprt[i]);
      
      // showSprite(& ShadowSprt[i], leJeu.lesCartes[carteJoueeSurLeTour[i]].data, i * (SoSpriteGetWidth(&ShadowSprt[i]) + 4) + 50, 72 + off);
      switch(i) {
      case 0:
	SoSpriteSetTranslate(& OAMSprt[SPRITE_OFF_CSET + 1], 2 * (SoSpriteGetWidth(& OAMSprt[SPRITE_OFF_CSET + 1]) + 4) + 50, 69 + 4);
	break;
      case 1:
	SoSpriteSetTranslate(& OAMSprt[SPRITE_OFF_CSET + 3], 0 * (SoSpriteGetWidth(& OAMSprt[SPRITE_OFF_CSET + 3]) + 4) + 50, 69 + 0);
	break;
      case 2:
	SoSpriteSetTranslate(& OAMSprt[SPRITE_OFF_CSET + 2], 1 * (SoSpriteGetWidth(& OAMSprt[SPRITE_OFF_CSET + 2]) + 4) + 50, 69 - 4);
	break;
      case 3:
	SoSpriteSetTranslate(& OAMSprt[SPRITE_OFF_CSET + 0], 3 * (SoSpriteGetWidth(& OAMSprt[SPRITE_OFF_CSET + 0]) + 4) + 50, 69 + 0);
      }
      // SoSpriteSetTranslate(& OAMSprt[SPRITE_OFF_CSET + i], i * (SoSpriteGetWidth(& OAMSprt[SPRITE_OFF_CSET + i]) + 4) + 50, 72 + off);
      SoSpriteSetPriority(& OAMSprt[SPRITE_OFF_CSET + i], SO_BKG_PRIORITY_0);
  
    }
  }

  // SoDisplayWaitForVBlankStart ();
  // SoDMA3Transfer (ShadowSprt, & OAMSprt[SPRITE_OFF_CSET], 4 * sizeof(SoSprite) / 4,  SO_DMA_32);
  
  SoKeysUpdate();
  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysPressed(SO_KEY_START));

  // Double attente...

  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysReleased(SO_KEY_START));

  SoDisplayWaitForVBlankStart();
  for (i = 0 ; i < 4 ; i++) {
    SoSpriteDisable(& OAMSprt[SPRITE_OFF_CSET + i]);
  }
  
  SoBkgEnable(1, false);

  writeStringToBkg("      ", 0, 6, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg("          ", 0, 13, 5, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);
  writeStringToBkg("                   ", 0, 6, 7, FIRST_ASCII_CHAR, OFFSET_FIRST_ASCII);

}

// Une animation qui est appelÅÈe quand un joueur rÅÈussit Å‡ tirer la lune...
void GDManimationShootDaMoon() {
  u16 shootIndex, daIndex, moonIndex;
  SoSprite tmp[3];
  u8 i;
  s16 spX, spY;

    SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;

  shootIndex = SoSpriteMemManagerLoad( & SHOOTSpriteAnimation);
  daIndex = SoSpriteMemManagerLoad( & DASpriteAnimation);
  moonIndex = SoSpriteMemManagerLoad( & MOONSpriteAnimation);

  // 1. Effacer les sprites...
  for (i = 0 ; i < 3 ; i++) {
    SoSpriteDisable(& tmp[i]);
  }

  spY = SHDAMOON_Y_MIN;

  for (spX = -64 ; spX < 88 ; spX += 3) {

    SoSpriteReset(& tmp[0]);
    SoSpriteCopyPropertiesFromAnimation(& tmp[0], & SHOOTSpriteAnimation);
    SoSpriteSetPalette(&tmp[0], PALETTE_SHOOT, SO_BKG_PRIORITY_0 );
    showSprite(&tmp[0], shootIndex, spX, spY);
    SoDisplayWaitForVBlankEnd();
    SoDisplayWaitForVBlankStart ();
    SoDMA3Transfer (tmp, &OAMSprt[SHDAMOON_OFF], 3 * sizeof(SoSprite) / 2,  SO_DMA_16);
  }

  spY += SoSpriteAnimationGetFrameHeight(& SHOOTSpriteAnimation) + SHDAMOON_Y_OFF;

  for (spX = 240 + 64 ; spX >= 88 ; spX -= 3) {

    SoSpriteReset(& tmp[1]);
    SoSpriteCopyPropertiesFromAnimation(& tmp[1], & DASpriteAnimation);
    SoSpriteSetPalette(&tmp[1], PALETTE_DA, SO_BKG_PRIORITY_0 );
    showSprite(&tmp[1], daIndex, spX, spY);
    SoDisplayWaitForVBlankEnd();
    SoDisplayWaitForVBlankStart ();
    SoDMA3Transfer (tmp, &OAMSprt[SHDAMOON_OFF], 3 * sizeof(SoSprite) / 2,  SO_DMA_16);
  }

  spY += SoSpriteAnimationGetFrameHeight(& DASpriteAnimation) + SHDAMOON_Y_OFF;

  for (spX = -64 ; spX < 88 ; spX += 3) {

    SoSpriteReset(& tmp[2]);
    SoSpriteCopyPropertiesFromAnimation(& tmp[2], & MOONSpriteAnimation);
    SoSpriteSetPalette(&tmp[2], PALETTE_MOON, SO_BKG_PRIORITY_0 );
    showSprite(&tmp[2], moonIndex, spX, spY);
    SoDisplayWaitForVBlankEnd();
    SoDisplayWaitForVBlankStart ();
    SoDMA3Transfer (tmp, &OAMSprt[SHDAMOON_OFF], 3 * sizeof(SoSprite) / 2,  SO_DMA_16);
  }

  for (i = 0 ; i < 60 ; i++) {
    SoDisplayWaitForVBlankEnd();
    SoDisplayWaitForVBlankStart();
  }

  // 1. Effacer les sprites...
  for (i = 0 ; i < 3 ; i++) {
    SoSpriteDisable(& tmp[i]);
  }
  
  SoDisplayWaitForVBlankStart ();
  SoDMA3Transfer (tmp, &OAMSprt[SHDAMOON_OFF], 3 * sizeof(SoSprite) / 2,  SO_DMA_16);

  SoSpriteMemManagerRelease(shootIndex);
  SoSpriteMemManagerRelease(daIndex);
  SoSpriteMemManagerRelease(moonIndex);

}

// Affiche un ÅÈcran de confirmation (OK, quoi...). Renvoie 'true' si le
// joueur a appuyÅÈ sur Start, false si il a voulu annuler (A ou B).
bool GDMafficherEcranConfirmation(u8 joueur_courant) {
  SoSprite *OAMSprt;

  OAMSprt = (SoSprite*) SO_REAL_OAM;

  SoDisplayWaitForVBlankStart();
  SoSpriteSetAnimationIndex(&OAMSprt[CURSEUR_SPR_NUM], curseurOKIndex);
  
  SoKeysUpdate();
  do {
    SoDisplayWaitForVBlankEnd();
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
  } while (! SoKeysPressed(SO_KEY_START | SO_KEY_A | SO_KEY_B));

  if (SoKeysPressed(SO_KEY_START)) return true;
  else return false;

}
