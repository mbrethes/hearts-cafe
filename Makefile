ROOTDIR = ~brethes/projets/Hearts
MUSDIR  = $(ROOTDIR)/Musics
EMU     = ~brethes/gbadev/BA/boyca

EMUFLAGS = -throttle -sound
CFLAGS   = -I $(ROOTDIR)/include -c -O2 -mthumb -mthumb-interwork -Wall -ffreestanding
ASFLAGS  = -mthumb-interwork
LDFLAGS  = -L $(ROOTDIR)/lib -Tlnkscript
LIBFLAG  = -lSocratesRls -lc -lgcc
CC = $(ROOTDIR)/../gba/devkit/bin/arm-agb-elf-gcc
AS = $(ROOTDIR)/../gba/devkit/bin/arm-agb-elf-as
LD = $(ROOTDIR)/../gba/devkit/bin/arm-agb-elf-ld
OC = $(ROOTDIR)/../gba/devkit/bin/arm-agb-elf-objcopy
RM = rm -f

# SOUND_O = IntroMod.o SplashScreenMod.o SelectPlayerMod.o
# SOUND_HDR = Mods.h

all : Hearts.bin

Hearts.bin : Hearts.elf
	$(OC) -v -O binary Hearts.elf Hearts.bin

Hearts.elf : Hearts.o Intro.o GameMenu.o crtbegin.o HeartsEngine.o CardManagement.o Player.o IA.o Humain.o Stuff.o GameDisplayManagement.o Palettes.o CarreauSprites.o CoeurSprites.o TrefleSprites.o PiqueSprites.o DiversSprites.o GameTiles.o GameBitmaps.o MenuDisplayManagement.o $(SOUND_O)
	$(LD) $(LDFLAGS) -o Hearts.elf crtbegin.o Hearts.o Intro.o GameMenu.o HeartsEngine.o CardManagement.o Player.o IA.o Humain.o Stuff.o GameDisplayManagement.o Palettes.o CarreauSprites.o CoeurSprites.o TrefleSprites.o PiqueSprites.o DiversSprites.o GameTiles.o GameBitmaps.o MenuDisplayManagement.o $(SOUND_O) $(LIBFLAG)

Intro.o : Intro.c Intro.h Palettes.h GameBitmaps.h $(SOUND_HDR)
	$(CC) $(CFLAGS) Intro.c

GameMenu.o : GameMenu.c GameMenu.h Player.h
	$(CC) $(CFLAGS) GameMenu.c

Hearts.o : Hearts.c Intro.h GameMenu.h Player.h
	$(CC) $(CFLAGS) Hearts.c

CardManagement.o : CardManagement.c CardManagement.h
	$(CC) $(CFLAGS) CardManagement.c

HeartsEngine.o : HeartsEngine.c HeartsEngine.h CardManagement.h Player.h IA.h GameDisplayManagement.h
	$(CC) $(CFLAGS) HeartsEngine.c

IA.o : IA.c IA.h HeartsEngine.h
	$(CC) $(CFLAGS) IA.c

Humain.o : Humain.c Humain.h HeartsEngine.h Stuff.h
	$(CC) $(CFLAGS) Humain.c

Player.o : Player.c Player.h IA.h Humain.h
	$(CC) $(CFLAGS) Player.c

Stuff.o : Stuff.c Stuff.h
	$(CC) $(CFLAGS) Stuff.c

GameDisplayManagement.o : GameDisplayManagement.c GameDisplayManagement.h HeartsEngine.h Palettes.h Player.h DiversSprites.h CarreauSprites.h CoeurSprites.h PiqueSprites.h TrefleSprites.h Stuff.h GameTiles.h
	$(CC) $(CFLAGS) GameDisplayManagement.c

MenuDisplayManagement.o : MenuDisplayManagement.c MenuDisplayManagement.h DiversSprites.h Palettes.h HeartsEngine.h Stuff.h GameBitmaps.h

CarreauSprites.o : CarreauSprites.c CarreauSprites.h
	$(CC) $(CFLAGS) CarreauSprites.c

CoeurSprites.o : CoeurSprites.c CoeurSprites.h
	$(CC) $(CFLAGS) CoeurSprites.c

TrefleSprites.o : TrefleSprites.c TrefleSprites.h
	$(CC) $(CFLAGS) TrefleSprites.c

PiqueSprites.o : PiqueSprites.c PiqueSprites.h
	$(CC) $(CFLAGS) PiqueSprites.c

DiversSprites.o : DiversSprites.c DiversSprites.h
	$(CC) $(CFLAGS) DiversSprites.c

Palettes.o : Palettes.c Palettes.h
	$(CC) $(CFLAGS) Palettes.c

GameTiles.o : GameTiles.c GameTiles.h
	$(CC) $(CFLAGS) GameTiles.c

GameBitmaps.o : GameBitmaps.c GameBitmaps.h
	$(CC) $(CFLAGS) GameBitmaps.c

crtbegin.o : crt0.S
	$(AS) $(ASFLAGS) crt0.S -o $@

clean :
	$(RM) *.o
	$(RM) *.elf
	$(RM) *~
	$(RM) Pics/*~
	$(RM) Palettes/*~
	$(RM) Maps/*~

run : Hearts.bin
	$(EMU) Hearts.bin $(EMUFLAGS)
