#include "particle_properties.hpp"

std::ostream& operator <<(std::ostream& os, const particle_properties& p){
        return os << p.name() << "( " << p.mass() << ", " << p.spin() << ", " << p.charge() << " )";
}

/*
float charge(particle_type p_type){
    switch(p_type) {
        case particle_type::undefined: return NAN;
        case particle_type::proton: return 1.;
        case particle_type::photon: return 0.;
        case particle_type::muon: return -1.;
        case particle_type::neutrino: return 0.;
    }
};

float mass(particle_type p_type){
    switch(p_type) {
        case particle_type::undefined: return NAN;
        case particle_type::proton: return 940.;
        case particle_type::photon: return 0.;
        case particle_type::muon: return 211.;
        case particle_type::neutrino: return 0.;
    }
};

std::string name(particle_type p_type){
    switch(p_type) {
        case particle_type::undefined: return std::string("UNDEFINED");
        case particle_type::proton: return std::string("Proton");
        case particle_type::photon: return std::string("Photon");
        case particle_type::muon: return std::string("Muon");
        case particle_type::neutrino: return std::string("Neutrino");
    }
};
*/
