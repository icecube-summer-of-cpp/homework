#ifndef PARTICLE
#define PARTICLE

/* 
 * 
 * PARTICLE
 * --------
 * A particle is a particle in particle physics sens. It has quantum 
 * numbers, position at a time point and energy and momentum. 
 * It has also a unique identifier.
 * 
 */

#include <cmath>            // for NAN
#include "unique_id.hpp"
#include "four_vector.hpp"
#include "particle_properties.hpp"
#include "gtest/gtest.h"

class particle{
    public:
        // constructors
        particle(): quantum_numb_(particle_type::undefined) {};
        particle(particle_type p_type): quantum_numb_(p_type) {};
        particle(const particle&) = default;
        particle(particle&&) = default;
        //particle(std::initializer_list<float> values);
       
        // assignments
        particle& operator=(const particle&) = default;
        particle& operator=(particle&&) = default;
        //particle& operator=(std::initializer_list<float> values);
        
        // destructor
        ~particle() = default;   

        // comparisons
        bool operator==(const particle& rhs) const { return (id_ == rhs.id()); }; // (energy_ == rhs.get_energy()) && 
        bool operator!=(const particle& rhs) const { return !(*this == rhs); };
       
        // getter and setter
        unique_id id() const { return id_; }
        //void set_energy(float energy){ energy_ = energy; }
        //float get_energy() const { return energy_; }
   
        // functionallity
        
    private:
        particle_type quantum_numb_; // mass, type, charge
        four_vector time_space_;
        four_vector energy_momentum_;
        unique_id id_;
    
    friend std::ostream& operator <<(std::ostream&, const particle&);
};

// printing
std::ostream& operator <<(std::ostream&, const particle&);

#endif
