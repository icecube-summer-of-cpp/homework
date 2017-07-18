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
        particle();
        particle(particle_type);
        particle(particle_type, four_vector, four_vector);
        particle(const particle&) = default;
        particle(particle&&) = default;
       
        // assignments
        particle& operator=(const particle&) = default;
        particle& operator=(particle&&) = default;
        
        // destructor
        ~particle() = default;   

        // comparisons
        bool operator==(const particle&) const;
        bool operator!=(const particle&) const;
       
        // getter and setter
        unique_id id() const;
        void set_energy(float energy);
        float get_energy() const;
   
        // functionallity
        
    private:
        particle_type quantum_numb_;
        four_vector time_space_;
        four_vector energy_momentum_;
        unique_id id_;
    
    friend std::ostream& operator <<(std::ostream&, const particle&);
};

// printing
std::ostream& operator <<(std::ostream&, const particle&);

#endif
