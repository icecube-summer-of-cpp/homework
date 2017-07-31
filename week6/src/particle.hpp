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
#include <vector>
#include <cassert>
#include <sstream>
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
        
        void set_energy_momentum(four_vector energy_momentum);
        four_vector get_energy_momentum() const;
        
        void set_spacetime_point(four_vector spacetime_point);
        four_vector get_spacetime_point() const;
        
        //particle_type get_particle() const;
        particle_properties get_properties() const {return properties_;};
        
        double get_mass() const;
        int get_charge() const;
        float get_spin() const;
        
        float get_zenith() const;
        float get_azimuth() const;
        
        // functionallity
        
    protected:
        particle_properties properties_;
        four_vector time_space_;
        four_vector energy_momentum_;
        unique_id id_;
    
    friend std::ostream& operator <<(std::ostream&, const particle&);
};

class sim_particle: public particle{
    public:
        enum class shape {unset, cascade, inice};
        
        sim_particle(): particle(), shape_(shape::unset) {};
        sim_particle(const sim_particle& p): particle(p), shape_(p.shape_) {};
        sim_particle(sim_particle&& p): particle(p), shape_(p.shape_) {};
        sim_particle& operator =(const sim_particle&) = default;
        sim_particle& operator =(sim_particle&&) = default;
        ~sim_particle() = default;
        
        shape get_shape(){return shape_;};
        void set_shape(shape s){shape_ = s;};
    
    private:
        shape shape_;
};

class reco_particle: public particle{
    public:
        enum class shape {unset, cascade, inice};
        enum class status {unset, good, bad};
        
        reco_particle(): particle(), shape_(shape::unset), status_(status::unset) {};
        reco_particle(const reco_particle& p): particle(p), shape_(shape::unset), status_(status::unset){};
        reco_particle(reco_particle&& p): particle(p), shape_(shape::unset), status_(status::unset){};
        reco_particle& operator =(const reco_particle&) = default;
        reco_particle& operator =(reco_particle&&) = default;
        ~reco_particle() = default;
        
        shape get_shape(){return shape_;};
        void set_shape(shape s){shape_ = s;};
        
        status get_status(){return status_;};
        void set_status(status s){status_ = s;};
    
    private:
        shape shape_;
        status status_;
};

// printing
std::ostream& operator <<(std::ostream&, const particle&);

#endif
