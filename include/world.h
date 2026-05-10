#pragma once

#include <string>
#include <stdint.h>
#include <vector>
#include "raylib.h"

enum CellType : uint8_t {
    AIR,
    SAND,
    WATER,
    STEEL,

    CELL_TYPE_COUNT
};

struct Cell {
    std::string name;
    float density; // kg/m^3
    bool liquid;
    bool solid;
    Color color;
};

class World {
    Cell cellTable[CELL_TYPE_COUNT] = {
        // name, density, liquid, solid, color, visible
        { "Air", 1.225f, false, false, {15, 0, 50, 255} },
        { "Sand", 1500.f, false, false, YELLOW },
        { "Water", 1000.f, true, false, BLUE },
        { "Steel", 7850.f, false, true, GRAY }
    };

    std::vector<uint8_t> cells;
    public:
    int width, height;
    int cellSize = 4;
    int dissipationStrength = 10;

    Texture2D texture;
    std::vector<Color> pixels = {};
    
    World(int _width, int _height);

    // cell
    uint8_t GetCell(int index) { if (!WithinBounds(index)) return 255; return cells[index]; }
    uint8_t GetCell(int x, int y) { size_t index = Index(x, y); return GetCell(index); }
    void SetCell(int index, uint8_t type) { cells[index] = type; }
    void SetCell(int x, int y, uint8_t type) { int index = Index(x, y); SetCell(index, type); }
    void Swap(int from, int to) { uint8_t tmp = GetCell(from); cells[from] = GetCell(to); cells[to] = tmp; }
    bool CanMoveTo(int from, int to);
    bool WithinBounds(int index) { return index >= 0 && index < width * height; }
    bool WithinBounds(int x, int y) { return x >= 0 && x < width && y >= 0 && y < height; }

    void Update();
    
    private:
    void UpdateCell(int index);
    void UpdateCell(int x, int y) { int index = Index(x, y); UpdateCell(index); }

    public:
    int Index(int x, int y) const { if (!(x >= 0 && x < width && y >= 0 && y < height)) return -1; return y * width + x; };

    // rendering
    void InitGraphics();
    void BuildPixelBuffer();
    void Draw();
};