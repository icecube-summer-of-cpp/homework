#include "particle_properties.hpp"

float charge(particle_type p_type){
    switch(p_type) {
        case particle_type::undefined: return NAN;
        case particle_type::proton: return 1.;
        case particle_type::photon: return 0.;
        case particle_type::muon: return -1.;
        case particle_type::neutrino: return 0.;
    }
}
