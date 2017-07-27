#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>


class Polynomial
{   

friend std::ostream& operator<< (std::ostream& stream, const Polynomial& p);
//friend Polynomial& Polynomial::operator=(Polynomial&& p); // Making it a friend to read other p's data IS NOT NECESSARY
friend Polynomial parabola(double a0, double a1, double a2);

public:
    Polynomial(const int& degree);
    Polynomial(const Polynomial& p) = default; // Copy constructor
    Polynomial& operator=(Polynomial&& p); // Move assignment.
    ~Polynomial() = default; // int's and vectors can be destroyed and release their memory
    
private:    
    int degree;
    std::vector<double> coeffs;
};

Polynomial parabola(double a0, double a1, double a2);
std::ostream& operator<< (std::ostream& stream, const Polynomial &rhs);
