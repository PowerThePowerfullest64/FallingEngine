#include <iostream>

#include "sim.h"

int main() {
    std::cout << "Hello, World!\n";

    Sim sim(48.f);

    sim.Run();

    return 0;
}