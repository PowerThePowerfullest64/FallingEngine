#include <iostream>

#include "sim.h"

int main() {
    std::cout << "Hello, World!\n";

    Sim sim(64.f);

    sim.Run();

    return 0;
}