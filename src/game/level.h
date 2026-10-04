#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "core/xpk.h"

// levels\NNN.dat : u32 count, then count * 60-byte records.
struct LevelObject {
    char    name[33];       // element name, resolved via data\elements.txt
    float   x, y, z;        // position
    float   ex, ey, ez;     // second float triplet (meaning not decoded yet)
    int32_t variant;
};

// Levels in the package: 000..010, 100, demo
bool LoadLevel(const XpkPackage& pkg, const std::string& file, std::vector<LevelObject>& out);
