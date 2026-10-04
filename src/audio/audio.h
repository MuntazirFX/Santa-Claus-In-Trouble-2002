#pragma once
// sfx\*.wav (PCM, from the package) + music\*.wav (loose file next to the game). Volumes from GameConfig.
class IAudio {
public:
    virtual ~IAudio() {}
    virtual void PlaySfx(const char* name) = 0;
    virtual void PlayMusic(const char* file) = 0;
};
