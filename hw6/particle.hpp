/* Module for particles including:
 *   Inheritable particle class
 *   Classes/structs for position, direction, velocity, 4-momentum, etc.
 *   Functions for interacting with particle class
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */



//Include guard
#ifndef __PARTICLE_HPP_INCLUDED__
#define __PARTICLE_HPP_INCLUDED__

#include <string>
#include "uniqueid.hpp"
#include "vectors.hpp"


class Particle
{
    public:
        Particle(const std::string& kind);

    private:
        const UniqueID id_;
        std::string kind_;
        double mass_;
        double charge_;
        CartesianVector position_;
        UnitVector direction_; 
        FourVector fourmomentum_;
};


#endif
