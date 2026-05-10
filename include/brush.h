#pragma once

#include "world.h"

#include <stdint.h>
#include <vector>

class Brush {
    public:
    int radius = 2;
    uint8_t type = SAND;

    std::vector<int> affectedCells = {};

    void Update(World& world, int mouseX, int mouseY);
    void Paint(World& world, bool erase=false);
    void ChangeRadius(int change);
    void Draw(const World& world);
};