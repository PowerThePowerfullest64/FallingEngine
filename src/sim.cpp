#include "sim.h"

#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <string>

void Sim::Run() {
    running = true;

    InitWindow(screenWidth, screenHeight, "FallingEngine");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    world.InitGraphics();

    while (running) {
        float deltaTime = GetFrameTime();

        accumulator += deltaTime;

        timer.Begin(); // start cell update
        while (accumulator >= updateDuration) {
            world.Update();

            accumulator -= updateDuration;
        }
        double updateMs = timer.End(); // end cell update

        brush.Update(world, GetMouseX(), GetMouseY());

        if (IsKeyPressed(KEY_ONE)) brush.type = SAND;
        if (IsKeyPressed(KEY_TWO)) brush.type = WATER;
        if (IsKeyPressed(KEY_THREE)) brush.type = STEEL;
        if (IsKeyPressed(KEY_FOUR)) brush.type = HYDROGEN;
        if (IsKeyPressed(KEY_FIVE)) brush.type = STEAM;

        brush.ChangeRadius(GetMouseWheelMove());

        if (IsMouseButtonDown(0)) brush.Paint(world);
        if (IsMouseButtonDown(1)) brush.Paint(world, true);


        timer.Begin(); // start buffer
        world.BuildPixelBuffer();
        double bufferMs = timer.End(); // end buffer

        timer.Begin(); // start drawing
        BeginDrawing();
        ClearBackground(BLACK);

        rlImGuiBegin();
        
        world.Draw();

        brush.Draw(world);

        double drawMs = timer.End(); // end drawing

        DrawFPS(4, 4);
        pw.Draw(updateMs, bufferMs, drawMs);

        rlImGuiEnd();

        EndDrawing();

        if (WindowShouldClose()) running = false;
    }

    rlImGuiShutdown();

    CloseWindow();
}

void Sim::SetUPS(float _ups) {
    ups = _ups;
    updateDuration = 1.f / ups;
    accumulator = 0.f;
}