// Summer of C++ 
// Quiz Week 3
// Solution by: Rene Reimann

/*
 * Write a class that serves as a unique identifier for other objects. 
 * I should be able to use this identifier as a class member to use for comparisons.
 * 
 * The class should compare equal to copies of itself, but not to objects 
 * created at the same time, on the same machine, in different processes.
 * 
 * It should not be computationally expensive to create subsequent IDs 
 * in one process. (Hint: You can use two private members: one that is 
 * expensive to compute and one that's cheap to compute. 
 * Unique ID objects compare equal if the two members compare equal.)
 * 
 * Follow the "Rule of Six."
 * 
 * Below is an example of a typical use case
 */

#ifndef PARTICLE
#define PARTICLE

#include <cmath>            // for NAN
#include "unique_id.hpp"

class particle{
    public:
        // i should get a unique identifier with the default constructor
        // of unique_id without having to do anything, so no need to include
        // it in the initialization list
        particle(): energy_(NAN) {};
       
        // no setter for ID.  just a getter.
        unique_id id() const { return id_; }
       
        void set_energy(float energy){ energy_ = energy; }
        float get_energy() const { return energy_; }
       
        bool operator==(const particle& rhs) const {
            return (energy_ == rhs.get_energy()) && (id_ == rhs.id());
        }; // neglect issues with float comparisons
       
        bool operator!=(const particle& rhs) const {
            return !(*this == rhs);
        }
 
    private:
        unique_id id_;
        float energy_;
};

#endif
