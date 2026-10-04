#pragma once
// Base object in a level: position, mesh, animation state. Player, Enemy, Bonus, Platform derive from it.
struct Entity {
    float x = 0, y = 0, z = 0;
    virtual ~Entity() {}
    virtual void Update(float dt) = 0;
};
