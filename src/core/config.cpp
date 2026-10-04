#include "core/config.h"
#include <cstdio>
#include <sstream>

bool GameConfig::LoadFromText(const std::string& text) {
    std::istringstream in(text);
    std::string line;
    bool any = false;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        std::istringstream ls(line);
        std::string key;
        if (!(ls >> key)) continue;
        int a = 0, b = 0;
        if (key == "Resolution") { if (ls >> a >> b) { width = a; height = b; any = true; } }
        else if (ls >> a) {
            if      (key == "Bitdepth")   bitdepth   = a;
            else if (key == "Fullscreen") fullscreen = a != 0;
            else if (key == "UseFog")     useFog     = a != 0;
            else if (key == "Controller") controller = a;
            else if (key == "Music")      music      = a;
            else if (key == "SFX")        sfx        = a;
            else continue;
            any = true;
        }
    }
    return any;
}

bool GameConfig::LoadFromFile(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return false;
    std::string s; char buf[256]; size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
    fclose(f);
    return LoadFromText(s);
}
