#include "world.h"

#include "random.h"
#include <iostream>

World::World(int _width, int _height) {
    width = _width;
    height = _height;

    cells.resize(width * height, AIR);
}

bool World::CanMoveTo(int from, int to) {
    if (to == -1) return false;

    uint8_t otherType = GetCell(to);

    if (otherType == 255) return false;
    if (cellTable[otherType].solid) return false;

    uint8_t type = GetCell(from);
    

    return cellTable[type].density > cellTable[otherType].density;
}

void World::Update() {
    for (int y = height-2; y >= 0; y--)
    if (randomInt()) for (int x = 0; x < width; x++) UpdateCell(x, y);
    else for (int x = width-1; x >= 0; x--) UpdateCell(x, y);
}

void World::UpdateCell(int index) {
    uint8_t type = GetCell(index);

    if (type == AIR) return; // don't update air for now
    if (cellTable[type].solid) return; // solids aren't affected by gravity

    int x = index % width;
    int y = index / width;

    int d = Index(x, y+1);

    if (CanMoveTo(index, d)) Swap(index, d);

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

    if (cellTable[type].liquid) {
        if (randomInt()) {
            for (int i = 1; i <= dissipationStrength; i++) {
                int nx = x+1;

                if (CanMoveTo(index, Index(nx, y))) {
                    x = nx;
                } else {
                    if (i != 1) {
                        Swap(index, Index(x, y));
                        return;
                    }
                }
            }
            for (int i = 1; i <= dissipationStrength; i++) {
                int nx = x-1;

                if (CanMoveTo(index, Index(nx, y))) {
                    x = nx;
                } else {
                    if (i != 1) {
                        Swap(index, Index(x, y));
                        return;
                    }
                }
            }
        } else {
            for (int i = 1; i <= dissipationStrength; i++) {
                int nx = x-1;

                if (CanMoveTo(index, Index(nx, y))) {
                    x = nx;
                } else {
                    if (i != 1) {
                        Swap(index, Index(x, y));
                        return;
                    }
                }
            }
            for (int i = 1; i <= dissipationStrength; i++) {
                int nx = x+1;

                if (CanMoveTo(index, Index(nx, y))) {
                    x = nx;
                } else {
                    if (i != 1) {
                        Swap(index, Index(x, y));
                        return;
                    }
                }
            }
        }
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
        pixels[i] = cellTable[type].color;
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