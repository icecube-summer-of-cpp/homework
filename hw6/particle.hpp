/* Module for particles including:
 *   Inheritable particle class
 *   Classes/structs for position, direction, velocity, 4-momentum, etc.
 *   Functions for interacting with particle class
 * Note that, for better or worse, all values are in SI (mks)
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */



//Include guard
#ifndef __PARTICLE_HPP_INCLUDED__
#define __PARTICLE_HPP_INCLUDED__

#include <string>
#include <iostream>
#include <math.h>
#include "uniqueid.hpp"
#include "vectors.hpp"

const double c_0 = 299792458;


class Particle
{
    public:
        // Constructor
        Particle(const std::string& kind);


        // Getter functions
        const UniqueID id() const {return id_;}
        const std::string name() const {return kind_;}
        const double restmass() const {return restmass_;}
        const double charge() const {return charge_;}
        const CartesianVector position() const {return position_;}
        const FourVector momentum() const {return fourmomentum_;}
        const UnitVector direction() const;
        const double energy() const;

        // Setter functions
        void set_position(const CartesianVector& pos);
        void set_position(const double x, const double y, const double z);
        void set_momentum(const FourVector& mom);
        void set_momentum(const CartesianVector& mom);


    private:
        const UniqueID id_;
        std::string kind_;
        double restmass_;
        double charge_;
        CartesianVector position_;
        FourVector fourmomentum_;
};


// Particle print function
std::ostream& operator<<(std::ostream& os, const Particle& p);

#endif
