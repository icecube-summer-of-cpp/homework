#include <iostream>
#include <cmath>
#include "event.hpp"
#include "particle.hpp"
#include "vectors.hpp"


void print_info(const Event& e)
{
    std::cout << "Event: " << e.type() << " with " << e.particle() << std::endl;
    std::cout << "  Vertex:    " << e.vertex() << " m" << std::endl;
    std::cout << "  Momentum:  " << e.momentum() << " kg m/s" << std::endl;
    std::cout << "  Energy:    " << e.energy() << " J" << std::endl;
    std::cout << "  Kinetic:   " << e.kinetic() << " J" << std::endl;
    std::cout << "  Direction: " << e.direction() << std::endl << std::endl;
}

int main()
{
    std::cout << "========== Testing Events ==========" << std::endl;
    Particle electron("electron");
    Event event("Cascade", electron);

    print_info(event);
}