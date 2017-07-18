#ifndef PARTICLE
#define PARTICLE

#include <cmath>            // for NAN
#include "unique_id.hpp"

/* constructor, assignment, move, destructor, comparison, getter, setters, tests, comments, printing, functionallity
 * 
 * PARTICLE
 * --------
 * + time / position 
 * + energy / momentum 
 * + unique_id
 * + quantum numbers
 * - direction
 * - mass
 * - type
 * - charge
 * 
 */

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
