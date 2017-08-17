#include <cassert>
#include <iostream>
#include <string>
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

    sim_particle p4(particle_type::photon);
    p4.set_shape(sim_particle::shape::dark);

    std::string shape;
    switch(p4.get_shape())
    {
        case sim_particle::shape::dark:
            shape = "dark";
            break;
        case sim_particle::shape::cascade_segment:
            shape = "cascade_segment";
            break;
        default:
            shape = "unset";
            break;
    }

    std::cout << "Particle p4: shape = " << shape << std::endl;

    reco_particle p5(particle_type::photon);
    p5.set_status(reco_particle::status::ok);

    std::string status;
    switch(p5.get_status())
    {
        case reco_particle::status::ok:
            status = "ok";
            break;
        case reco_particle::status::failure:
            status = "failure";
            break;
        default:
            status = "unset";
            break;
    }

    std::cout << "Particle p5: status = " << status << std::endl;
}
