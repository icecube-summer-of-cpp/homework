#include <cassert>
#include <iostream>
#include <vector>

#include "particle.hpp"
#include "unique_id.hpp"

int main()
{
    particle p1;
    std::cout << "Particle p1: id = " << p1.id() << std::endl;

    particle p2(particle_type::numu);
    std::cout << "Particle p2: id = " << p2.id() << std::endl;

    assert(p1 != p2);

    unique_id test_id(p1.id());
    std::vector<particle> particles = {p1, p2};

    assert(test_id == particles.front().id());

    particle p3(particle_type::photon);
    std::cout << "Particle p3: id = " << p3.id() << std::endl;
}
