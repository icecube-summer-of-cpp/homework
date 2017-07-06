/* Module for vectors designed to work for particle module
 * Includes:
 *   CartesianVector class (3D vector with x, y, z)
 *   UnitVector class (3D vector normalized to length 1)
 *   FourVector class (4D vector with w, x, y, z - designed for four-momenta)
 *   Functions for manipulating vectors
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */


//Include guard
#ifndef __VECTORS_HPP_INCLUDED__
#define __VECTORS_HPP_INCLUDED__

#include <math.h>


class CartesianVector
{
    public:
        // Default constructor
        CartesianVector(double x=0, double y=0, double z=0)
        : x_(x), y_(y), z_(z) {};

        // Length function
        double length();

    protected:
        double x_, y_, z_;
};


class UnitVector : public CartesianVector
{
    public:
        // Default constructor
        UnitVector(double x=1, double y=0, double z=0);

    private:
        void normalize();
};


class FourVector
{
    public:
        // Default constructor
        FourVector(double w=0, double x=0, double y=0, double z=0)
        : w_(w), x_(x), y_(y), z_(z) {};

    private:
        double w_, x_, y_, z_;
};


#endif
