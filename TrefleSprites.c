#include "TrefleSprites.h"

// Fichier contenant plein de trucs amusants


#include "Pics/2TrefleSpriteAnimation.dat"
#include "Pics/3TrefleSpriteAnimation.dat"
#include "Pics/4TrefleSpriteAnimation.dat"
#include "Pics/5TrefleSpriteAnimation.dat"
#include "Pics/6TrefleSpriteAnimation.dat"
#include "Pics/7TrefleSpriteAnimation.dat"
#include "Pics/8TrefleSpriteAnimation.dat"
#include "Pics/9TrefleSpriteAnimation.dat"
#include "Pics/10TrefleSpriteAnimation.dat"
#include "Pics/VTrefleSpriteAnimation.dat"
#include "Pics/DTrefleSpriteAnimation.dat"
#include "Pics/RTrefleSpriteAnimation.dat"
#include "Pics/AsTrefleSpriteAnimation.dat"


const SoSpriteAnimation TrefleSpriteAnimation[] = {
  { true, 32, 64, 1, (u8*) _2TrefleSpriteAnimationData },  // le 2
  { true, 32, 64, 1, (u8*) _3TrefleSpriteAnimationData },  // le 3
  { true, 32, 64, 1, (u8*) _4TrefleSpriteAnimationData },  // le 4
  { true, 32, 64, 1, (u8*) _5TrefleSpriteAnimationData },  // le 5
  { true, 32, 64, 1, (u8*) _6TrefleSpriteAnimationData },  // le 6
  { true, 32, 64, 1, (u8*) _7TrefleSpriteAnimationData },  // le 7
  { true, 32, 64, 1, (u8*) _8TrefleSpriteAnimationData },  // le 8
  { true, 32, 64, 1, (u8*) _9TrefleSpriteAnimationData },  // le 9
  { true, 32, 64, 1, (u8*) _10TrefleSpriteAnimationData }, // le 10
  { true, 32, 64, 1, (u8*) VTrefleSpriteAnimationData },   // le valet
  { true, 32, 64, 1, (u8*) DTrefleSpriteAnimationData },   // la dame
  { true, 32, 64, 1, (u8*) RTrefleSpriteAnimationData },   // le roi
  { true, 32, 64, 1, (u8*) AsTrefleSpriteAnimationData }   // l'as
};


