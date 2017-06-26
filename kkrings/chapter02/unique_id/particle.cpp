#include <cmath>
#include "particle.hpp"

bool particle::operator!=(const particle& other) const
{
    return std::abs(energy - other.energy) > 0. || id_ != other.id();
}

bool particle::operator==(const particle& other) const
{
    return !(*this != other);
}
