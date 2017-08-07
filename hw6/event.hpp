/* Module for simulated or reconstructed particle events including:
 *   Inheritable event class
 *   Functions for interacting with event class
 * Note that, for better or worse, all values are in SI (mks)
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */



//Include guard
#ifndef __EVENT_HPP_INCLUDED__
#define __EVENT_HPP_INCLUDED__

#include <iostream>
#include <cmath>
#include "particle.hpp"
#include "vectors.hpp"


class Event
{
    public:
        // Constructor
        Event(const std::string& type, const Particle& particle)
        : type_(type), particle_(particle) {};

        // Getter functions
        const Particle particle() const {return particle_;}
        const std::string type() const {return type_;}

        // Getter functions of particle attributes
        const CartesianVector vertex() const {return particle_.position();}
        const FourVector momentum() const {return particle_.momentum();}
        const UnitVector direction() const {return particle_.direction();}
        const double energy() const {return particle_.energy();}
        const double kinetic() const {return particle_.kinetic();}


    protected:
        const Particle particle_;
        std::string type_;
};


#endif
