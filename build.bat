g++ -std=c++23 -Iraylib/include -IcustomHeaders -Iinclude main.cpp ^
-Iimgui-master -IrlImGui-main ^
src/*.cpp ^
customHeaders/*.cpp ^
imgui-master/imgui.cpp imgui-master/imgui_draw.cpp imgui-master/imgui_widgets.cpp imgui-master/imgui_tables.cpp ^
rlImGui-main/rlImGui.cpp ^
-Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o main.exe