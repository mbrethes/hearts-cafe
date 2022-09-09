#include "Intro.h"
#include "Mods.h"

#define VSPEED 7



// Renvoie une première seed.
u32 InitIntro() {
  u32 seed=0;
  u32 seedmax;
  u8 j;
  s16 i;
  s16 fademax;

  // Test...

  // SoIntManagerEnableInterruptMaster  ( );
  // SoIntManagerEnableInterrupt(SO_INTERRUPT_TYPE_TIMER_0 | SO_INTERRUPT_TYPE_TIMER_1);

  // while (1) {
  //  SoDisplayWaitForVBlankStart();
    //afm_update();
    //afm_sync();
  //  SoDisplayWaitForVBlankEnd();
  // }

  SoMode4RendererEnable();
  SoPaletteSetBlack(SO_SCREEN_PALETTE, true);
  SoMode4RendererDrawImage(& IntroPicImage);
  SoDisplayWaitForVBlankStart();
  SoMode4RendererFlip();

  
  
  for (i = 0 ; i < SO_FADE_MAX - 1 ; i++)
    {
      for (j = 0 ; j < VSPEED ; j++) {
	SoDisplayWaitForVBlankEnd();
	SoDisplayWaitForVBlankStart();
      }
      SoPaletteFadePalette(&SO_SCREEN_PALETTE[240], &introPicPalette[240], i, false);
    }

  fademax = 0 ;
  j = 0;

  SoKeysUpdate();
  do {
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
    SoDisplayWaitForVBlankEnd();
    
    if (fademax < SO_FADE_MAX - 1 && SoMathModulus(seed, VSPEED) == 0) {
      for (j = 0 ; j < 15 ; j++)
	SoPaletteFadePalette(&SO_SCREEN_PALETTE[j * 16], &introPicPalette[j * 16], fademax, false);
      
      fademax++;
    }

    seed ++;
  } while (seed < (60 * 5) && ! SoKeysPressed(SO_KEY_ANY));

  seedmax = seed + (60 * 5);

  for (i = fademax < SO_FADE_MAX - 1 ? fademax : SO_FADE_MAX - 2; i >= 0 ; i--) {
    for (j = 0 ; j < VSPEED ; j++) {
      SoDisplayWaitForVBlankEnd();
      SoDisplayWaitForVBlankStart();
    }
    for (j = 0 ; j < 15 ; j++)
      SoPaletteFadePalette(&SO_SCREEN_PALETTE[j * 16], &introPicPalette[j * 16], i, false);
  }

  for (i = SO_FADE_MAX - 2 ; i >= 0 ; i--) {
    for (j = 0 ; j < VSPEED ; j++) {
      SoDisplayWaitForVBlankEnd();
      SoDisplayWaitForVBlankStart();
    }
    SoPaletteFadePalette(&SO_SCREEN_PALETTE[240], &introPicPalette[240], i, false);
  }

  // Intro à Zero...
  /* 
     afm_install();
  
     afm_init(&INTROMOD);
     afm_sound_param(0x3F,1);

  SoPaletteSetBlack(SO_SCREEN_PALETTE, true);
  SoMode4RendererDrawImage(& IntroZeroPicImage);
  SoDisplayWaitForVBlankStart();
  SoMode4RendererFlip();

  for (i = 0 ; i < SO_FADE_MAX - 1 ; i++)
    {
      for (j = 0 ; j < VSPEED ; j++) {
	SoDisplayWaitForVBlankEnd();
	SoDisplayWaitForVBlankStart();
		
      }
      SoPaletteFadePalette(SO_SCREEN_PALETTE, introZeroPicPalette, i, true);
    }

  j = 0;

  SoKeysUpdate();
  do {
    SoKeysUpdate();
    SoDisplayWaitForVBlankStart();
    SoDisplayWaitForVBlankEnd();
    
    seed ++;
  } while (seed < seedmax && ! SoKeysPressed(SO_KEY_ANY));

  for (i = SO_FADE_MAX - 2; i >= 0 ; i--) {
    for (j = 0 ; j < VSPEED ; j++) {
      SoDisplayWaitForVBlankEnd();
      afm_sound_param((0x3F * i) / (SO_FADE_MAX - 2),1);
      SoDisplayWaitForVBlankStart();
    }
    SoPaletteFadePalette(SO_SCREEN_PALETTE, introZeroPicPalette, i, true);
  }

  afm_deinit();

  */

  return seed;
}

u32 GameSplashScreen(u32 sd) {

  u32 seed;
  u8 j;
  s16 i;

  seed = sd;

  u8 loop;
  /*
  afm_install();

  afm_init(&SPLASHMOD);
  afm_sound_param(0x3F,1);
  */

  SoPaletteSetBlack(SO_SCREEN_PALETTE, true);
  SoMode4RendererDrawImage(& SplashScreenImage);
  SoDisplayWaitForVBlankStart();
  SoMode4RendererFlip();
  SoMode4RendererDrawImage(& SplashScreen2Image);

  for (i = 0 ; i < SO_FADE_MAX - 1 ; i++)
    {
      for (j = 0 ; j < VSPEED ; j++) {
	SoDisplayWaitForVBlankEnd();
	SoDisplayWaitForVBlankStart();
      }
      SoPaletteFadePalette(SO_SCREEN_PALETTE, splashScreenPalette, i , true);
    }

  loop = 0;

  SoKeysUpdate();
  do {
    SoKeysUpdate();

    // afm_update();
    while (! SoDisplayIsInVBlank ()) {

      seed ++;
    }
    // afm_sync();
    if (loop == 0) {
      SoMode4RendererFlip();
      loop ++;
    }    
    else if (loop > (VSPEED* 2)) loop = 0;
    else loop++;

    while (SoDisplayIsInVBlank()) {
      seed ++;
    }
  } while (! SoKeysPressed(SO_KEY_START));

  for (i = SO_FADE_MAX - 2; i >= 0 ; i--) {
    for (j = 0 ; j < VSPEED ; j++) {
      SoDisplayWaitForVBlankEnd();
      // afm_sound_param((0x3F * i) / (SO_FADE_MAX - 2),1);
      SoDisplayWaitForVBlankStart();
    }
    SoPaletteFadePalette(SO_SCREEN_PALETTE, splashScreenPalette, i, true);
  }

  // afm_deinit();

  return seed;
}

