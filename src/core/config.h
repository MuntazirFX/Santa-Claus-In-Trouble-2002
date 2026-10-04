#pragma once
#include <string>

// config.txt: "Key value" lines (Resolution W H, Bitdepth, Fullscreen, UseFog, Controller, Music, SFX)
struct GameConfig {
    int  width = 800, height = 600, bitdepth = 16;
    bool fullscreen = true, useFog = true;
    int  controller = 2;      // input mode
    int  music = 85;          // 0..100
    int  sfx = 100;           // 0..100

    bool LoadFromText(const std::string& text);
    bool LoadFromFile(const char* path);
};
