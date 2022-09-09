#ifndef __GAME_TILES_HEADER__
#define __GAME_TILES_HEADER__

#include <Socrates.h>

#define FIRST_ASCII_CHAR 0x21
#define OFFSET_FIRST_ASCII     15
#define OFFSET_FIRST_PERSO     109
#define OFFSET_FIRST_TABLE     509
#define OFFSET_FIRST_SUPP      521
#define PERSO_WIDTH  10
#define PERSO_HEIGHT 10
#define NB_PERSO     4

// Définitions pour les animations...

#define JOHN_POS_X   4
#define JOHN_POS_Y   4
#define JOHN_NBTILES 3
#define KAY_POS_X    13
#define KAY_POS_Y    3
#define KAY_NBTILES  2
#define HCR_POS_X    24
#define HCR_POS_Y    6
#define HCR_NBTILES  2
#define ELUF_POS_X   34
#define ELUF_POS_Y   4
#define ELUF_NBTILES 3

extern const SoTileSet MainGameTilesTileSet;

extern const SoBkgMap BG1Map;

extern const SoBkgMap BG2Map;

extern const SoBkgMap BG3Map;

#endif
