# SantaEngine
Independent engine for the original Santa Claus in Trouble (2002). Uses the game's own data (xmas.xpk, levels, music).
Layout: src/core (xpk, config) · src/game · src/gfx · src/audio · src/input · src/ui · platform/ios · platform/win32.
Windows: cmake -S . -B build -A Win32   iOS: push -> GitHub Actions builds unsigned IPA (put xmas.xpk in assets/).
