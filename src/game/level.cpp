#include "game/level.h"
#include <cstring>

static uint32_t U32(const uint8_t* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24); }
static float    F32(const uint8_t* p) { uint32_t u = U32(p); float f; memcpy(&f, &u, 4); return f; }

bool LoadLevel(const XpkPackage& pkg, const std::string& file, std::vector<LevelObject>& out) {
    std::vector<uint8_t> d;
    if (!pkg.Read(file, d) || d.size() < 4) return false;
    uint32_t n = U32(d.data());
    if (d.size() != 4 + (size_t)n * 60) return false;

    out.clear(); out.reserve(n);
    for (uint32_t i = 0; i < n; ++i) {
        const uint8_t* r = d.data() + 4 + (size_t)i * 60;
        LevelObject o;
        size_t len = 0; while (len < 32 && r[len] != 0 && r[len] != 0xCD) ++len;   // NUL or 0xCD padded
        memcpy(o.name, r, len); o.name[len] = 0;
        o.x = F32(r + 32); o.y = F32(r + 36); o.z = F32(r + 40);
        o.ex = F32(r + 44); o.ey = F32(r + 48); o.ez = F32(r + 52);
        o.variant = (int32_t)U32(r + 56);
        out.push_back(o);
    }
    return true;
}
