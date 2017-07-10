/* Module for vectors designed to work for particle module
 * Includes:
 *   CartesianVector struct (3D vector with x, y, z)
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
#include <iostream>


class UnitVector
{
    public:
        // Constructors
        UnitVector(double x=1, double y=0, double z=0);

        // Getter functions
        const double x() const {return x_;}
        const double y() const {return y_;}
        const double z() const {return z_;}
        const double& operator[](int i) const;

    private:
        double x_, y_, z_;
        void normalize();
};


class CartesianVector
{
    public:
        // Constructors
        CartesianVector(double x=0, double y=0, double z=0)
        : x_(x), y_(y), z_(z) {};
        CartesianVector(const UnitVector& v)
        : x_(v.x()), y_(v.y()), z_(v.z()) {};

        // Getter functions
        const double x() const {return x_;}
        const double y() const {return y_;}
        const double z() const {return z_;}
        double& operator[](int i);
        const double& operator[](int i) const;

        // Arithmetic functions
        CartesianVector& operator+=(const CartesianVector& rhs);
        CartesianVector& operator-=(const CartesianVector& rhs);
        CartesianVector& operator*=(const double rhs);

    private:
        double x_, y_, z_;
};


class FourVector
{
    public:
        // Default constructor
        FourVector(double w=0, double x=0, double y=0, double z=0)
        : w_(w), x_(x), y_(y), z_(z) {};

        // Getter functions
        const double w() const {return w_;}
        const double x() const {return x_;}
        const double y() const {return y_;}
        const double z() const {return z_;}
        double& operator[](int i);
        const double& operator[](int i) const;

        // Arithmetic functions
        FourVector& operator+=(const FourVector& rhs);
        FourVector& operator-=(const FourVector& rhs);
        FourVector& operator*=(const double rhs);

    private:
        double w_, x_, y_, z_;
};


// Vector print functions
std::ostream& operator<<(std::ostream& os, const UnitVector& v);
std::ostream& operator<<(std::ostream& os, const CartesianVector& v);
std::ostream& operator<<(std::ostream& os, const FourVector& v);


// Vector magnitude functions
double mag(const CartesianVector& v);
double mag(const FourVector& v);


// Vector product functions
double dot(const CartesianVector& u, const CartesianVector& v);
double dot(const FourVector& u, const FourVector& v);
CartesianVector cross(const CartesianVector& u, const CartesianVector& v);


// Arithmetic functions
CartesianVector operator+(const CartesianVector& lhs, const CartesianVector& rhs);
CartesianVector operator-(const CartesianVector& lhs, const CartesianVector& rhs);
CartesianVector operator*(const CartesianVector& lhs, const double rhs);
CartesianVector operator*(const double lhs, const CartesianVector& rhs);

FourVector operator+(const FourVector& lhs, const FourVector& rhs);
FourVector operator-(const FourVector& lhs, const FourVector& rhs);
FourVector operator*(const FourVector& lhs, const double rhs);
FourVector operator*(const double lhs, const FourVector& rhs);


#endif
