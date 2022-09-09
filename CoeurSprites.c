#include "CoeurSprites.h"

// Fichier contenant plein de trucs amusants


#include "Pics/2CoeurSpriteAnimation.dat"
#include "Pics/3CoeurSpriteAnimation.dat"
#include "Pics/4CoeurSpriteAnimation.dat"
#include "Pics/5CoeurSpriteAnimation.dat"
#include "Pics/6CoeurSpriteAnimation.dat"
#include "Pics/7CoeurSpriteAnimation.dat"
#include "Pics/8CoeurSpriteAnimation.dat"
#include "Pics/9CoeurSpriteAnimation.dat"
#include "Pics/10CoeurSpriteAnimation.dat"
#include "Pics/VCoeurSpriteAnimation.dat"
#include "Pics/DCoeurSpriteAnimation.dat"
#include "Pics/RCoeurSpriteAnimation.dat"
#include "Pics/AsCoeurSpriteAnimation.dat"


const SoSpriteAnimation CoeurSpriteAnimation[] = {
  { true, 32, 64, 1, (u8*) _2CoeurSpriteAnimationData },  // le 2
  { true, 32, 64, 1, (u8*) _3CoeurSpriteAnimationData },  // le 3
  { true, 32, 64, 1, (u8*) _4CoeurSpriteAnimationData },  // le 4
  { true, 32, 64, 1, (u8*) _5CoeurSpriteAnimationData },  // le 5
  { true, 32, 64, 1, (u8*) _6CoeurSpriteAnimationData },  // le 6
  { true, 32, 64, 1, (u8*) _7CoeurSpriteAnimationData },  // le 7
  { true, 32, 64, 1, (u8*) _8CoeurSpriteAnimationData },  // le 8
  { true, 32, 64, 1, (u8*) _9CoeurSpriteAnimationData },  // le 9
  { true, 32, 64, 1, (u8*) _10CoeurSpriteAnimationData }, // le 10
  { true, 32, 64, 1, (u8*) VCoeurSpriteAnimationData },   // le valet
  { true, 32, 64, 1, (u8*) DCoeurSpriteAnimationData },   // la dame
  { true, 32, 64, 1, (u8*) RCoeurSpriteAnimationData },   // le roi
  { true, 32, 64, 1, (u8*) AsCoeurSpriteAnimationData }   // l'as
};


