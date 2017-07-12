#include <iostream>
#include <cmath>
#include "event.hpp"
#include "particle.hpp"
#include "vectors.hpp"


void print_info(const Particle& p)
{
    std::cout << "Particle: " << p << std::endl;
    std::cout << "  Rest mass: " << p.restmass() << " kg" << std::endl;
    std::cout << "  Charge:    " << p.charge() << " C" << std::endl;
    std::cout << "  Position:  " << p.position() << " m" << std::endl;
    std::cout << "  Distance:  " << mag(p.position()) << " m" << std::endl;
    std::cout << "  Momentum:  " << p.momentum() << " kg m/s" << std::endl;
    std::cout << "  Energy:    " << p.energy() << " J" << std::endl;
    std::cout << "  Kinetic:   " << p.kinetic() << " J" << std::endl;
    std::cout << "  Direction: " << p.direction() << std::endl << std::endl;
}

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
    electron.set_position(CartesianVector(0,0,10));
    electron.set_energy(1.6e-10);
    electron.set_direction(UnitVector(0,0,-1));
    print_info(electron);

    Event event("Cascade", electron);

    print_info(event);
}