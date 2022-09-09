#include "Stuff.h"

// Cette fonction convertit un entier non signé en chaine
// de caractères ASCII. La chaine est remplie jusqu'à len
// (str doit faire au moins len+1). Le buffer passé en 
// paramètre sera rempli de caractères fill (code ASCII).
// le nombre est aligné à droite.
void u2str(u32 value, char* str, u8 len, char fill) {
  u8 i;
  u32 curValue;

  for (i = 0 ; i < len ; i++) {
    str[i] = fill;
  }
  
  i = len;

  do {
    i--;
    curValue = value % 10;
    value = value / 10;
    str[i] = '0' + curValue;
  } while (i > 0 && value > 0);
}

// Attend qu'une touche soit pressée, et retourne.
// optimisation pour bouffer moins de CPU.
void keyPressWait() {
  SoKeysUpdate();

  do { SoKeysUpdate();
  SoDisplayWaitForVBlankEnd();
  SoDisplayWaitForVBlankStart();
  } while(! SoKeysPressed (SO_KEY_ANY));
}

// Permet de mettre le sprite a une certaine valeur
// de palette, en mode 16 couleurs.
void SoSpriteSetPalette(SoSprite * sp, u16 palIndex, u8 priority) {
  u16 val = 0;
  val = val | (palIndex << 12) | (priority << 10);
  
  
  sp->m_Attribute[2] = sp->m_Attribute[2] & 0x03FF;
  sp->m_Attribute[2] = sp->m_Attribute[2] | val;
}

// Met la priorité du sprite à jour...
void SoSpriteSetPriority(SoSprite *sp, u8 priority) {
  u16 val = 0;
  val = val | (priority << 10);
  
  
  sp->m_Attribute[2] = sp->m_Attribute[2] & 0xF3FF;
  sp->m_Attribute[2] = sp->m_Attribute[2] | val;
}


// Initialise le contenu du sprite à 0...
void SoSpriteReset(SoSprite * sp) {
  u8 i;

  for (i = 0 ; i < 4 ; i++)
    sp->m_Attribute[i] = 0;
}

// Ecrit une chaine de caractères sur le BKG donné.
// Sympa, non ?
void writeStringToBkg(char * str, u8 bkgNum, u8 posX, u8 posY, u16 firstAsciiCharInSet, u16 offsetFirstAscii) {
  u8 i;
  u16 tileIdx;

  for (i = 0 ; str[i] != 0 ; i++) {
    if (str[i] == ' ') tileIdx = 0;
    else tileIdx = str[i] - firstAsciiCharInSet + offsetFirstAscii;
    SoBkgWrite (bkgNum, posX + i, posY, 1, &tileIdx);
  }  
}

// Affiche un image aux coordonnées données. Ne fonctionne qu'en
// mode 4, bien évidemment...
// Inspiré des fonctions de SGADE.
// Ne met pas à jour l'affichage.
void drawBitmapToCoords(const SoImage * image, u8 posX, u8 posY) {
  u8 x, y;
  u8* arr = (u8 *) SoImageGetData(image);

  for (x = 0 ; x < SoImageGetWidth(image) ; x++) {
    for (y = 0 ; y < SoImageGetHeight(image) ; y++) {
      SoMode4RendererDrawPixel (posX + x, posY + y, arr[y * SoImageGetWidth(image) + x]);
    }
  }
}

// Cette fonction échange matériellement 2 tiles dans la tile vram.
void swapTiles(u16 tile1Idx, u16 tile2Idx, u8 charBase) {
  u8 buffer[64];

  SoDMA0Transfer((u8 *)(SO_BKG_CHARBASE(charBase) + (tile1Idx * 64) + 0x06000000), buffer, 16, SO_DMA_32);
  SoDMA0Transfer((u8 *)(SO_BKG_CHARBASE(charBase) +(tile2Idx * 64) + 0x06000000), (u8 *)(SO_BKG_CHARBASE(charBase) + (tile1Idx * 64) + 0x06000000), 16, SO_DMA_32);
  SoDMA0Transfer(buffer, (u8 *)(SO_BKG_CHARBASE(charBase) + (tile2Idx * 64) + 0x06000000), 16, SO_DMA_32);
}
