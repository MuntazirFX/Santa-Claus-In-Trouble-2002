#pragma once
#include <string>
#include <unordered_map>

// data\elements.txt:  ELEMENT "name" { FILE "gfx\x.x"  RADIUS r  SCALING s  SPEED v  WALKANIM n  TYPE ENEMY|PLATTFORM|... }
struct Element {
    std::string name, meshFile, type;
    float radius = 1, scaling = 1, speed = 0;
    int   walkAnim = 0;
};
class ElementCatalog {
public:
    bool Parse(const std::string& text);            // TODO
    const Element* Find(const std::string& name) const;
private:
    std::unordered_map<std::string, Element> map_;
};
