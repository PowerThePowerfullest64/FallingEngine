#pragma once

#include <string>
#include <stdint.h>
#include <vector>
#include "raylib.h"

enum MaterialType : uint8_t {
    AIR,
    SAND,
    WATER,
    STEEL,

    CELL_TYPE_COUNT
};

enum class MatterState : uint8_t {
    GAS,
    POWDER,
    LIQUID,
    SOLID
};

struct CellMaterial {
    const char* name;
    float density; // kg/m^3
    MatterState state;
    Color color;
};

class World {
    public:
    static inline constexpr CellMaterial materialTable[CELL_TYPE_COUNT] = {
        // name, density, matter state, color
        { "Air", 1.225f, MatterState::GAS, {15, 0, 50, 255} },
        { "Sand", 1500.f, MatterState::POWDER, YELLOW },
        { "Water", 1000.f, MatterState::LIQUID, BLUE },
        { "Steel", 7850.f, MatterState::SOLID, GRAY }
    };

    private:
    std::vector<uint8_t> materialType;
    std::vector<float> gasAmount;
    // add some flow direction for liquids?
    public:
    int width, height;
    int cellSize = 4;
    int dissipationStrength = 10;

    Texture2D texture;
    std::vector<Color> pixels = {};
    
    World(int _width, int _height);

    // cell
    uint8_t GetCell(int index) { if (!WithinBounds(index)) return 255; return materialType[index]; }
    uint8_t GetCell(int x, int y) { int index = Index(x, y); return GetCell(index); }
    void SetCell(int index, uint8_t type) { materialType[index] = type; if (materialTable[type].state != MatterState::GAS) gasAmount[index] = 0.f; }
    void SetCell(int x, int y, uint8_t type) { int index = Index(x, y); SetCell(index, type); }
    void Swap(int from, int to) { uint8_t tmpMat = GetCell(from); materialType[from] = GetCell(to); materialType[to] = tmpMat; float tmpGas = gasAmount[from]; gasAmount[from] = gasAmount[to]; gasAmount[to] = tmpGas; }
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