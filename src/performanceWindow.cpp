#include "performanceWindow.h"

#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

void PerformanceWindow::Draw(double updateMs, double bufferMs, double drawMs) {
    ImGui::Begin("Performance Analyzer");

    ImGui::Text("Update time: %.2f ms", updateMs);
    ImGui::Text("Buffer time: %.2f ms", bufferMs);
    ImGui::Text("Draw time : %.2f ms", drawMs);

    ImGui::End();
}