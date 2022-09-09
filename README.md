# Hearts Café

A Game Boy Advance game I developed for the Hearts Dev Compo hosted by https://www.gbadev.org/ in October 2002.

The source code had been lingering on [one of my old websites](http://thieumsweb.free.fr/english/gbahearts.html) for ages now, maybe it's better that it goes here.

A binary version is also available [here](https://gbadev.org/demos.php?showinfo=394).

## About

This is a fully functional card game of Hearts, tested both on emulator and on real hardware. It does not have sound.

The specificity of this game is that it allows several human players to share the same Game Boy, with a waiting
screen hiding the cards while the device switches hands. It also features two different AIs to allow for
1-player play. One of the AIs is dumb (it plays a random valid card at every turn), the other is "smart" (it follows
a predefined strategy thought in advance to minimize losses). Both AIs do not cheat, that is they act like they do
not know the state of their opponent's cards.

The original instructions about the game are in the [how to play.txt](how to play.txt) file.

With its reasonably slick interface and lack of obvious bugs, this game won the first place of the competition
back then, and I was very happy about that ;-).

## Build instructions

Note that the last time I cross-compiled this game was in 2003 using [Devkit Advance](http://devkitadv.sourceforge.net/) on Linux. Your mileage may vary.

Clone this repository, place yourself in the root directory containing the [Makefile](Makefile), edit the Makefile to give the paths of your Devkit, and type "make".

The game relies on the [SGADE](https://sourceforge.net/projects/sgade/), an open-source library. Its source code is not included,
instead you get precompiled binaries in the [lib](lib) folder. If you want to get the source code, it should
still be available on sourceforge (see Credits below).

If you need to run the game on real hardware, it needs to be patched to include a specific checksum that is required by
the GBA upon startup. But it should run as-is on an emulator (tested on [BoycottAdvance](https://gbadev.org/tools.php?showinfo=200)).


## Credits

Many thanks to Jaap Sutter and Mark T. Price, developers of the Socrates Game Boy Advance Development Engine (or SGADE),
The library was well-documented and relatively simple to use. I am eternally grateful to them.


## Disclaimer

I am in no way affiliated with Nintendo, and this game was developed with no proprietary resources or knowledge
provided by the company. _Nintendo_, _Game Boy_ and _Game Boy Advance_ are trademarks of Nintendo. I
solely use those words to describe on which hardware the game runs.
