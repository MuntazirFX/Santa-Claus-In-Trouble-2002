#include "core/xpk.h"
#include <algorithm>

static bool ReadU32(FILE* f, uint32_t& v) {
    uint8_t b[4];
    if (fread(b, 1, 4, f) != 4) return false;
    v = b[0] | (b[1] << 8) | (b[2] << 16) | ((uint32_t)b[3] << 24);
    return true;
}

static bool ReadU32Array(FILE* f, uint32_t n, std::vector<uint32_t>& out) {
    out.resize(n);
    for (uint32_t i = 0; i < n; ++i)
        if (!ReadU32(f, out[i])) return false;
    return true;
}

std::string XpkPackage::Key(const std::string& name) {
    std::string k = name;
    for (char& c : k) {
        if (c == '/') c = '\\';
        else c = (char)tolower((unsigned char)c);
    }
    return k;
}

bool XpkPackage::Open(const char* path) {
    Close();
    f_ = fopen(path, "rb");
    if (!f_) { fprintf(stderr, "Package file not found: '%s'\n", path); return false; }
    path_ = path;

    fseek(f_, 0, SEEK_END);
    long fileSize = ftell(f_);
    fseek(f_, 0, SEEK_SET);

    uint32_t n = 0, nameBlock = 0, total = 0;
    std::vector<uint32_t> nameOffs, sizes, skip;

    bool ok = ReadU32(f_, n) && n > 0 && n < 100000
           && ReadU32Array(f_, n, nameOffs)
           && ReadU32(f_, nameBlock) && nameBlock < 16u * 1024 * 1024;

    std::vector<char> block;
    if (ok) {
        block.resize(nameBlock);
        ok = fread(block.data(), 1, nameBlock, f_) == nameBlock
          && ReadU32(f_, total)
          && ReadU32Array(f_, n, sizes);
    }
    if (!ok) { fprintf(stderr, "Bad package header: '%s'\n", path); Close(); return false; }

    // File data is stored at the end of the package, back to back.
    uint64_t sum = 0;
    for (uint32_t s : sizes) sum += s;
    if (sum != total || sum > (uint64_t)fileSize) {
        fprintf(stderr, "Package size mismatch: '%s'\n", path); Close(); return false;
    }
    uint64_t pos = (uint64_t)fileSize - sum;

    for (uint32_t i = 0; i < n; ++i) {
        if (nameOffs[i] >= nameBlock) { Close(); return false; }
        std::string name(&block[nameOffs[i]]);   // block is null-terminated per name
        names_.push_back(name);
        entries_[Key(name)] = { pos, sizes[i] };
        pos += sizes[i];
    }
    return true;
}

void XpkPackage::Close() {
    if (f_) { fclose(f_); f_ = nullptr; }
    names_.clear();
    entries_.clear();
    path_.clear();
}

bool XpkPackage::Exists(const std::string& name) const {
    return entries_.count(Key(name)) != 0;
}

bool XpkPackage::Read(const std::string& name, std::vector<uint8_t>& out) const {
    auto it = entries_.find(Key(name));
    if (it == entries_.end() || !f_) {
        fprintf(stderr, "File not found: \"%s\"\n", name.c_str());
        return false;
    }
    out.resize(it->second.size);
#ifdef _WIN32
    if (_fseeki64(f_, (long long)it->second.offset, SEEK_SET) != 0)
#else
    if (fseeko(f_, (off_t)it->second.offset, SEEK_SET) != 0)
#endif
    {
        fprintf(stderr, "Failed to seek package file position: '%s'\n", name.c_str());
        return false;
    }
    return fread(out.data(), 1, out.size(), f_) == out.size();
}
