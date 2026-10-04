#pragma once
#include <cstdint>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

// xmas.xpk package reader (little-endian, uncompressed archive).
//
// Layout:
//   u32      count N
//   u32[N]   offset of each name inside the name block
//   u32      name block size
//   char[]   name block (null-terminated strings, e.g. "gfx\\platt_t_full.x")
//   u32      total size of all file data
//   u32[N]   file sizes
//   u32[N*2] two more tables (unknown, not needed for reading)
//   ...      file data, back to back, in table order; ends at end of file
class XpkPackage {
public:
    ~XpkPackage() { Close(); }

    bool Open(const char* path);
    void Close();

    bool Exists(const std::string& name) const;
    bool Read(const std::string& name, std::vector<uint8_t>& out) const;

    size_t Count() const { return entries_.size(); }
    const std::vector<std::string>& Names() const { return names_; }

private:
    struct Entry { uint64_t offset; uint32_t size; };
    static std::string Key(const std::string& name);  // lowercase, '/' -> '\\'

    mutable FILE* f_ = nullptr;
    std::string path_;
    std::vector<std::string> names_;
    std::unordered_map<std::string, Entry> entries_;
};
