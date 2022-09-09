#ifndef __STUFF_HEADER__
#define __STUFF_HEADER__

/* Ce module contient tous les bouts de code qui n'ont
   pas leur place ailleurs. */

#include <Socrates.h>

void u2str(u32 value, char* str, u8 len, char fill);
void keyPressWait();
void SoSpriteSetPalette(SoSprite * sp, u16 palIndex, u8 priority);
void SoSpriteSetPriority(SoSprite *sp, u8 priority);
void SoSpriteReset(SoSprite * sp);

void writeStringToBkg(char * str, u8 bkgNum, u8 posX, u8 posY, u16 firstAsciiCharInSet, u16 offsetFirstAscii);

void drawBitmapToCoords(const SoImage * image, u8 posX, u8 posY);

void swapTiles(u16 tile1Idx, u16 tile2Idx, u8 charBase);

#endif
