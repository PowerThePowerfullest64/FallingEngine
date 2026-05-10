#pragma once

#include "raylib.h"

class Timer {
    public:
    double start;
    void Begin() { start = GetTime(); }
    double End() { return (GetTime() - start) * 1000.f; }

};