#include "CarreauSprites.h"

// Fichier contenant plein de trucs amusants


#include "Pics/2CarreauSpriteAnimation.dat"
#include "Pics/3CarreauSpriteAnimation.dat"
#include "Pics/4CarreauSpriteAnimation.dat"
#include "Pics/5CarreauSpriteAnimation.dat"
#include "Pics/6CarreauSpriteAnimation.dat"
#include "Pics/7CarreauSpriteAnimation.dat"
#include "Pics/8CarreauSpriteAnimation.dat"
#include "Pics/9CarreauSpriteAnimation.dat"
#include "Pics/10CarreauSpriteAnimation.dat"
#include "Pics/VCarreauSpriteAnimation.dat"
#include "Pics/DCarreauSpriteAnimation.dat"
#include "Pics/RCarreauSpriteAnimation.dat"
#include "Pics/AsCarreauSpriteAnimation.dat"


const SoSpriteAnimation CarreauSpriteAnimation[] = {
  { true, 32, 64, 1, (u8*) _2CarreauSpriteAnimationData },  // le 2
  { true, 32, 64, 1, (u8*) _3CarreauSpriteAnimationData },  // le 3
  { true, 32, 64, 1, (u8*) _4CarreauSpriteAnimationData },  // le 4
  { true, 32, 64, 1, (u8*) _5CarreauSpriteAnimationData },  // le 5
  { true, 32, 64, 1, (u8*) _6CarreauSpriteAnimationData },  // le 6
  { true, 32, 64, 1, (u8*) _7CarreauSpriteAnimationData },  // le 7
  { true, 32, 64, 1, (u8*) _8CarreauSpriteAnimationData },  // le 8
  { true, 32, 64, 1, (u8*) _9CarreauSpriteAnimationData },  // le 9
  { true, 32, 64, 1, (u8*) _10CarreauSpriteAnimationData }, // le 10
  { true, 32, 64, 1, (u8*) VCarreauSpriteAnimationData },   // le valet
  { true, 32, 64, 1, (u8*) DCarreauSpriteAnimationData },   // la dame
  { true, 32, 64, 1, (u8*) RCarreauSpriteAnimationData },   // le roi
  { true, 32, 64, 1, (u8*) AsCarreauSpriteAnimationData }   // l'as
};


