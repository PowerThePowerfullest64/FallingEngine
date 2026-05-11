#include "world.h"

#include "random.h"
#include <iostream>

World::World(int _width, int _height) {
    width = _width;
    height = _height;

    materialType.resize(width * height, AIR);
    flowDirection.resize(width * height, false);
    updated.resize(width * height, false);
}

bool World::CanMoveTo(int from, int to) {
    if (to == -1) return false;

    uint8_t otherType = GetCell(to);

    if (otherType == 255) return false;
    if (materialTable[otherType].state == MatterState::SOLID) return false;

    uint8_t type = GetCell(from);

    if (materialTable[type].state == MatterState::GAS && materialTable[otherType].state != MatterState::GAS) return false;
    
    if (materialTable[type].state == MatterState::GAS && materialTable[otherType].state == MatterState::GAS) {
        return materialTable[type].density < materialTable[otherType].density;
    }

    return materialTable[type].density > materialTable[otherType].density;
}

void World::Update() {
    for (int i = 0; i < updated.size(); i++) updated[i] = false;
    for (int y = height-2; y >= 0; y--)
    if (randomInt()) for (int x = 0; x < width; x++) UpdateCell(x, y);
    else for (int x = width-1; x >= 0; x--) UpdateCell(x, y);

    for (int y = 1; y < height; y++)
    if (randomInt()) for (int x = 0; x < width; x++) UpdateGas(x, y);
    else for (int x = width-1; x >= 0; x--) UpdateGas(x, y);
}

void World::UpdateCell(int index) {
    uint8_t type = GetCell(index);
    if (materialTable[type].state == MatterState::GAS) return;
    if (materialTable[type].state == MatterState::SOLID) return; // solids aren't affected by gravity and physics
    if (updated[index]) return; // already updated, skip

    int x = index % width;
    int y = index / width;

    int d = Index(x, y+1);

    if (CanMoveTo(index, d)) { Swap(index, d); return; };

    if (randomInt()) {
        int dr = Index(x+1, y+1);
        if (CanMoveTo(index, dr)) { Swap(index, dr); return; }
        int dl = Index(x-1, y+1);
        if (CanMoveTo(index, dl)) { Swap(index, dl); return; }
    } else {
        int dl = Index(x-1, y+1);
        if (CanMoveTo(index, dl)) { Swap(index, dl); return; }
        int dr = Index(x+1, y+1);
        if (CanMoveTo(index, dr)) { Swap(index, dr); return; }
    }

    if (materialTable[type].state == MatterState::LIQUID) {
        if (flowDirection[index] == true) {
            int r = Index(x+1, y);
            if (CanMoveTo(index, r)) { Swap(index, r); return; }
            else flowDirection[index] = false;
        }
        else {
            int l = Index(x-1, y);
            if (CanMoveTo(index, l)) { Swap(index, l); return; }
            else flowDirection[index] = true;
        }
    }
}

void World::UpdateGas(int index) {
    uint8_t type = GetCell(index);
    if (materialTable[type].state != MatterState::GAS) return; // only update gases
    //if (type == AIR) return;
    if (updated[index]) return;

    bool didMove = false;
    int x, y;
    GetXY(x, y, index);

    int u = Index(x, y-1);

    if (CanMoveTo(index, u)) { Swap(index, u); didMove = true; GetXY(x, y, index); }

    else if (randomInt()) {
        int ur = Index(x+1, y-1);
        if (CanMoveTo(index, ur)) { Swap(index, ur); didMove = true; GetXY(x, y, index); }
        int ul = Index(x-1, y-1);
        if (CanMoveTo(index, ul)) { Swap(index, ul); didMove = true; GetXY(x, y, index); }
    } else {
        int ul = Index(x-1, y-1);
        if (CanMoveTo(index, ul)) { Swap(index, ul); didMove = true; GetXY(x, y, index); }

        else {
            int ur = Index(x+1, y-1);
            if (CanMoveTo(index, ur)) { Swap(index, ur); didMove = true; GetXY(x, y, index); }
        }
    }

    if (randomInt()) {
        if (randomInt()) {
            int r = Index(x+1, y);
            if (CanMoveTo(index, r)) { Swap(index, r); GetXY(x, y, index); }
        } else {
            int l = Index(x-1, y);
            if (CanMoveTo(index, l)) { Swap(index, l); GetXY(x, y, index); }
        }
    }

    if (didMove) return;

    if (flowDirection[index] == true) {
        int r = Index(x+1, y);
        if (CanMoveTo(index, r)) { Swap(index, r); return; }
        else flowDirection[index] = false;
    } else {
        int l = Index(x-1, y);
        if (CanMoveTo(index, l)) { Swap(index, l); return; }
        else flowDirection[index] = true;
    }
}

void World::InitGraphics() {
    pixels.resize(width * height, {15, 0, 50, 255});

    Image image = GenImageColor(width, height, {15, 0, 50, 255});
    texture = LoadTextureFromImage(image);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    UnloadImage(image);
}

void World::BuildPixelBuffer() {
    for (int i = 0; i < width*height; i++) {
        uint8_t type = GetCell(i);
        pixels[i] = materialTable[type].color;
    }

    UpdateTexture(texture, pixels.data());
}

void World::Draw() {
    DrawTexturePro(
        texture,
        {0,0, (float)width, (float)height},
        {0,0, (float)width*cellSize, (float)height*cellSize},
        {0,0},
        0.f,
        WHITE
    );
}