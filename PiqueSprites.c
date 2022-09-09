#include "PiqueSprites.h"

// Fichier contenant plein de trucs amusants


#include "Pics/2PiqueSpriteAnimation.dat"
#include "Pics/3PiqueSpriteAnimation.dat"
#include "Pics/4PiqueSpriteAnimation.dat"
#include "Pics/5PiqueSpriteAnimation.dat"
#include "Pics/6PiqueSpriteAnimation.dat"
#include "Pics/7PiqueSpriteAnimation.dat"
#include "Pics/8PiqueSpriteAnimation.dat"
#include "Pics/9PiqueSpriteAnimation.dat"
#include "Pics/10PiqueSpriteAnimation.dat"
#include "Pics/VPiqueSpriteAnimation.dat"
#include "Pics/DPiqueSpriteAnimation.dat"
#include "Pics/RPiqueSpriteAnimation.dat"
#include "Pics/AsPiqueSpriteAnimation.dat"


const SoSpriteAnimation PiqueSpriteAnimation[] = {
  { true, 32, 64, 1, (u8*) _2PiqueSpriteAnimationData },  // le 2
  { true, 32, 64, 1, (u8*) _3PiqueSpriteAnimationData },  // le 3
  { true, 32, 64, 1, (u8*) _4PiqueSpriteAnimationData },  // le 4
  { true, 32, 64, 1, (u8*) _5PiqueSpriteAnimationData },  // le 5
  { true, 32, 64, 1, (u8*) _6PiqueSpriteAnimationData },  // le 6
  { true, 32, 64, 1, (u8*) _7PiqueSpriteAnimationData },  // le 7
  { true, 32, 64, 1, (u8*) _8PiqueSpriteAnimationData },  // le 8
  { true, 32, 64, 1, (u8*) _9PiqueSpriteAnimationData },  // le 9
  { true, 32, 64, 1, (u8*) _10PiqueSpriteAnimationData }, // le 10
  { true, 32, 64, 1, (u8*) VPiqueSpriteAnimationData },   // le valet
  { true, 32, 64, 1, (u8*) DPiqueSpriteAnimationData },   // la dame
  { true, 32, 64, 1, (u8*) RPiqueSpriteAnimationData },   // le roi
  { true, 32, 64, 1, (u8*) AsPiqueSpriteAnimationData }   // l'as
};


