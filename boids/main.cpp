#include <iostream>
#include "src/simulator.hpp"

int main() {
    Simulator* sim = new Simulator();
    sim->run_sim();

    return 0;
}
