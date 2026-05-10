#pragma once

#include "world.h"
#include "brush.h"
#include "timer.h"
#include "performanceWindow.h"

class Sim {
    bool running = false;
    const int screenWidth = 1024, screenHeight = 1024;

    World world = World(256, 256);
    Brush brush;

    float ups;
    float updateDuration;
    float accumulator;

    Timer timer;

    PerformanceWindow pw;
    
    public:
    Sim(float _ups) { SetUPS(_ups); }
    void Run();
    void SetUPS(float _ups);
};