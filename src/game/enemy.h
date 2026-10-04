#pragma once
#include "game/entity.h"
// Troll, raven, snowman ... behaviour driven by elements.txt (SPEED, RADIUS) + waypoints.
struct Enemy : Entity { void Update(float) override {} /* TODO */ };
