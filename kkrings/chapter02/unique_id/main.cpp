#include <cassert>
#include <iostream>
#include <vector>

#include "particle.hpp"
#include "unique_id.hpp"

int main()
{
    particle p1(1000.);

    std::cout << "Particle p1: energy = " << p1.energy
              << ", id = " << p1.id()
              << std::endl;

    particle p2(1000.);

    std::cout << "Particle p2: energy = " << p2.energy
              << ", id = " << p2.id()
              << std::endl;

    assert(p1 != p2);

    unique_id testid(p1.id());
    std::vector<particle> particles = {p1, p2};
    assert(testid == particles.front().id());
}
