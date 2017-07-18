#ifndef PARTICLE_PROPERTIES
#define PARTICLE_PROPERTIES

/*
 * Particle properties
 * 
 * We define enum classes for 
 *      particle_type
 *      fit_status
 *      sim_particles
 *      reco_shape
 * 
 * We also define functions that give properties of the enums, 
 * e.g. charge(particle_type)
 * 
 */

// includes 
#include <cmath>
#include <iostream>
#include <sstream>

// first lets define the enums
enum class particle_type { undefined, proton, photon, muon, neutrino };
enum class fit_status {ok, failed, partial, warn};
enum class sim_particle {primary, cascade_segment, dark};
enum class reco_shape {inice};

// parameters of a particle_type
float charge(particle_type);
float mass(particle_type);
std::string name(particle_type); 

// get the int of an enum 
template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

#endif
