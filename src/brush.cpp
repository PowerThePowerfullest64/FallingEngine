#include "brush.h"

#include "imgui.h"

void Brush::Update(World& world, int mouseX, int mouseY) {
    if (ImGui::GetIO().WantCaptureMouse) return;

    int x = mouseX / world.cellSize;
    int y = mouseY / world.cellSize;

    affectedCells.clear();

    for (int yo = -radius; yo <= radius; yo++)
    for (int xo = -radius; xo <= radius; xo++) {
        int index = world.Index(x+xo, y+yo);

        if (index == -1) continue; // out of bounds; skip

        affectedCells.push_back(index);
    }
}

void Brush::Paint(World& world, bool erase) {
    if (ImGui::GetIO().WantCaptureMouse) return;

    for (int index : affectedCells) {
        if (erase) world.SetCell(index, AIR);
        else world.SetCell(index, type);
    }
}

void Brush::ChangeRadius(int change) {
    if (ImGui::GetIO().WantCaptureMouse) return;

    radius += change;

    radius = std::max(radius, 0);
}

void Brush::Draw(const World& world) {
    if (ImGui::GetIO().WantCaptureMouse) return;

    for (int index : affectedCells) {
        int wx = index % world.width;
        int wy = index / world.height;

        int x = wx * world.cellSize;
        int y = wy * world.cellSize;

        DrawRectangleLines(x, y, world.cellSize, world.cellSize, WHITE);
    }
}