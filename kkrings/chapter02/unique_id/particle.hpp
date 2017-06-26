#ifndef UNIQUE_ID_PARTICLE_HPP
#define UNIQUE_ID_PARTICLE_HPP

#include <cmath>
#include "unique_id.hpp"

class particle
{
    public:
        particle(double energy=NAN) : energy(energy) {};
        unique_id id() const {return id_;};

        bool operator!=(const particle& other) const;
        bool operator==(const particle& other) const;

        double energy;

    private:
        unique_id id_;
};

#endif
