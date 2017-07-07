/* Module for particles including:
 *   Inheritable particle class
 *   Classes/structs for position, direction, velocity, 4-momentum, etc.
 *   Functions for interacting with particle class
 * Note that, for better or worse, all values are in SI (mks)
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */


#include "particle.hpp"

// Particle constructor
Particle::Particle(const std::string& kind)
{
    kind_ = kind;
    restmass_ = 1;
    charge_ = 0;
    fourmomentum_ = FourVector(restmass_ * c_0);
}


// Particle getter functions
const double Particle::energy() const
{
    return fourmomentum_[0]*c_0;
}


const UnitVector Particle::direction() const
{
    return UnitVector(fourmomentum_.x(),fourmomentum_.y(),fourmomentum_.z());
}


// Particle setter functions
void Particle::set_position(const CartesianVector& pos)
{
    position_ = pos;
}

void Particle::set_position(const double x, const double y, const double z)
{
    position_ = CartesianVector(x,y,z);
}

void Particle::set_momentum(const FourVector& mom)
{
    if (dot(mom,mom)*c_0*c_0 == restmass_*restmass_) {
        fourmomentum_ = mom;
    }
    // TODO: Add error in else statement
}

void Particle::set_momentum(const CartesianVector& mom)
{
    fourmomentum_ = FourVector(0,mom.x(),mom.y(),mom.z());
    double p2 = -1*dot(fourmomentum_,fourmomentum_);
    fourmomentum_[0] = sqrt(restmass_*restmass_ * c_0*c_0 + p2);
}


// Particle print function
std::ostream& operator<<(std::ostream& os, const Particle& p)
{
    return os << p.name();
}
