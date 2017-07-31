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
#include <map>
#include <iostream>
#include <sstream>
enum class particle_type { unknown, proton, photon, muon, neutrino };

using properties = std::tuple<double, unsigned, int, std::string>;
    
const std::map<particle_type, properties>property_map = 
            {{particle_type::unknown, properties{0, 0, 0, "UNKNOWN"}},
             {particle_type::proton, properties{1000, 1, 1, "Proton"}},
             {particle_type::photon, properties{0, 2, 0, "Photon"}},
             {particle_type::muon, properties{110, 1, -1, "Muon"}},
             {particle_type::neutrino, properties{1000, 1, 1, "Neutrino"}}};
             
class particle_properties{
        public:
            // constructors
            particle_properties(particle_type type): type_(type), property_(property_map.at(type)) {};
            particle_properties(): type_(particle_type::unknown), property_(property_map.at(particle_type::unknown)) {};
            particle_properties(const particle_properties&) = default;
            particle_properties(particle_properties&&) = default;
            // destructor
            ~particle_properties() = default;
            // assignments
            particle_properties& operator=(const particle_properties&) = default;
            particle_properties& operator=(particle_properties&&) = default;

            particle_type type() const {return type_;}
            double mass() const { return std::get<0>(property_); }
            float spin() const { return 0.5*std::get<1>(property_); }
            int charge() const { return std::get<2>(property_); }
            std::string name() const { return std::get<3>(property_); }
            
        private:
            particle_type type_;
            properties property_;
};

std::ostream& operator <<(std::ostream& os, const particle_properties& p);

/*
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
*/
#endif
