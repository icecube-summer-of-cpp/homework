#ifndef PARTICLE_PROPERTIES
#define PARTICLE_PROPERTIES

/*
 * Particle properties
 * 
 * 
 * 
 */
 
#include <cmath>
#include <iostream>

// returns the integer of the enum 
template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

enum class particle_type { undefined, proton, photon, muon, neutrino };
enum class fit_status {ok, failed, partial};
enum class sim_particle {primary, cascade_segment, dark};
enum class reco_status {ok, failed, warn};
enum class reco_shape {inice};

// parameters of a particle_type
float charge(particle_type p_type);

#endif
