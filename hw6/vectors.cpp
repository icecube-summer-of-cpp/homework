/* Module for vectors designed to work for particle module
 * Includes:
 *   CartesianVector class (3D vector with x, y, z)
 *   UnitVector class (3D vector normalized to length 1)
 *   FourVector class (4D vector with w, x, y, z - designed for four-momenta)
 *   Functions for manipulating vectors
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */

// #define NDEBUG
#include <cassert>
#include "vectors.hpp"


// Unit vector constructors
UnitVector::UnitVector(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
    normalize();
}


// Unit vector bracket overload
const double& UnitVector::operator[](int i) const
{
    if      (i==0) {return x_;}
    else if (i==1) {return y_;}
    else if (i==2) {return z_;}
    // TODO: Add error in else statement
}


// Unit vector normalization function
void UnitVector::normalize()
{
    double len = mag(*this);
    if (len==0 || isnan(len)) {
        x_ = 0;
        y_ = 0;
        z_ = 1;
    }
    else {
        x_ /= len;
        y_ /= len;
        z_ /= len;
    }
    assert(mag(*this)>.9999999999 && mag(*this)<1.0000000001);
}



// Cartesian vector bracket overloads
double& CartesianVector::operator[](int i)
{
    if      (i==0) {return x_;}
    else if (i==1) {return y_;}
    else if (i==2) {return z_;}
    // TODO: Add error in else statement
}

const double& CartesianVector::operator[](int i) const
{
    if      (i==0) {return x_;}
    else if (i==1) {return y_;}
    else if (i==2) {return z_;}
    // TODO: Add error in else statement
}


// Cartesian vector arithmetic operations
CartesianVector& CartesianVector::operator+=(const CartesianVector& rhs)
{
    x_ += rhs.x();
    y_ += rhs.y();
    z_ += rhs.z();
    return *this;
}

CartesianVector& CartesianVector::operator-=(const CartesianVector& rhs)
{
    x_ -= rhs.x();
    y_ -= rhs.y();
    z_ -= rhs.z();
    return *this;
}

CartesianVector& CartesianVector::operator*=(const double rhs)
{
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;
    return *this;
}


CartesianVector operator+(const CartesianVector& lhs, const CartesianVector& rhs)
{
    CartesianVector temp(lhs);
    return temp += rhs;
}

CartesianVector operator-(const CartesianVector& lhs, const CartesianVector& rhs)
{
    CartesianVector temp(lhs);
    return temp -= rhs;
}

CartesianVector operator*(const CartesianVector& lhs, const double rhs)
{
    CartesianVector temp(lhs);
    return temp *= rhs;
}

CartesianVector operator*(const double lhs, const CartesianVector& rhs)
{
    CartesianVector temp(rhs);
    return temp *= lhs;
}



// Four-vector bracket overloads
double& FourVector::operator[](int i)
{
    if      (i==0) {return w_;}
    else if (i==1) {return x_;}
    else if (i==2) {return y_;}
    else if (i==3) {return z_;}
    // TODO: Add error in else statement
}

const double& FourVector::operator[](int i) const
{
    if      (i==0) {return w_;}
    else if (i==1) {return x_;}
    else if (i==2) {return y_;}
    else if (i==3) {return z_;}
    // TODO: Add error in else statement
}


// Four-vector arithmetic operations
FourVector& FourVector::operator+=(const FourVector& rhs)
{
    w_ += rhs.w();
    x_ += rhs.x();
    y_ += rhs.y();
    z_ += rhs.z();
    return *this;
}

FourVector& FourVector::operator-=(const FourVector& rhs)
{
    w_ -= rhs.w();
    x_ -= rhs.x();
    y_ -= rhs.y();
    z_ -= rhs.z();
    return *this;
}

FourVector& FourVector::operator*=(const double rhs)
{
    w_ *= rhs;
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;
    return *this;
}


FourVector operator+(const FourVector& lhs, const FourVector& rhs)
{
    FourVector temp(lhs);
    return temp += rhs;
}

FourVector operator-(const FourVector& lhs, const FourVector& rhs)
{
    FourVector temp(lhs);
    return temp -= rhs;
}

FourVector operator*(const FourVector& lhs, const double rhs)
{
    FourVector temp(lhs);
    return temp *= rhs;
}

FourVector operator*(const double lhs, const FourVector& rhs)
{
    FourVector temp(rhs);
    return temp *= lhs;
}


// Vector print functions
std::ostream& operator<<(std::ostream& os, const UnitVector& v)
{
    return os << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
}

std::ostream& operator<<(std::ostream& os, const CartesianVector& v)
{
    return os << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
}

std::ostream& operator<<(std::ostream& os, const FourVector& v)
{
    return os << "(" << v.w() << "," << v.x() << "," << v.y() << "," << v.z() << ")";
}


// Vector magnitude functions
double mag(const CartesianVector& v)
{
    assert(dot(v,v)>=0 || isnan(dot(v,v)));
    return sqrt(dot(v,v));
}

double mag(const FourVector& v)
{
    return sqrt(dot(v,v));
}


// Vector product functions
double dot(const CartesianVector& u, const CartesianVector& v)
{
    return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

double dot(const FourVector& u, const FourVector& v)
{
   return u.w()*v.w() - u.x()*v.x() - u.y()*v.y() - u.z()*v.z();
}

CartesianVector cross(const CartesianVector& u, const CartesianVector& v)
{
    return CartesianVector(u.y()*v.z() - u.z()*v.y(),
                           u.z()*v.x() - u.x()*v.z(),
                           u.x()*v.y() - u.y()*v.x());
}

