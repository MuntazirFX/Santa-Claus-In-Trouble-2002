// g++ -std=c++17 -Isrc tools/test_data.cpp src/core/*.cpp src/game/level.cpp -o test_data && ./test_data /path/to/game
#include "core/xpk.h"
#include "core/config.h"
#include "game/level.h"
#include <cstdio>
#include <string>
int main(int argc, char** argv) {
    std::string dir = argc > 1 ? argv[1] : ".";
    GameConfig c; printf("config: %d  %dx%d fog=%d music=%d sfx=%d\n", c.LoadFromFile((dir + "/config.txt").c_str()), c.width, c.height, c.useFog, c.music, c.sfx);
    XpkPackage pkg; if (!pkg.Open((dir + "/xmas.xpk").c_str())) return 1;
    const char* lv[] = {"000","001","002","003","004","005","006","007","008","009","010","100","demo"};
    for (auto n : lv) { std::vector<LevelObject> o; bool ok = LoadLevel(pkg, std::string("levels\\") + n + ".dat", o);
        printf("level %s: %s %zu objects%s%s\n", n, ok ? "ok" : "FAIL", o.size(), o.empty() ? "" : "  first=", o.empty() ? "" : o[0].name); }
}
