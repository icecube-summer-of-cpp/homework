/* Module for particles including:
 *   Inheritable particle class
 *   Classes/structs for position, direction, velocity, 4-momentum, etc.
 *   Functions for interacting with particle class
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */


#include "particle.hpp"

// Particle constructor
Particle::Particle(const std::string& kind)
{
    kind_ = kind;
    mass_ = 1;
    charge_ = 0;
}