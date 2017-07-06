/* Module for vectors designed to work for particle module
 * Includes:
 *   CartesianVector class (3D vector with x, y, z)
 *   UnitVector class (3D vector normalized to length 1)
 *   FourVector class (4D vector with w, x, y, z - designed for four-momenta)
 *   Functions for manipulating vectors
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */


#include "vectors.hpp"

//Cartesian vector length function
double CartesianVector::length()
{
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}

// Unit vector constructor
UnitVector::UnitVector(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
    normalize();
}


// Unit vector normalization function
void UnitVector::normalize()
{
    double len = length();
    x_ /= len;
    y_ /= len;
    z_ /= len;
}
