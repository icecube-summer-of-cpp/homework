#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <initializer_list>

class Polynomial
{   

friend std::ostream& operator<< (std::ostream& stream, const Polynomial& p); // the operator can't be a member => friend
//friend Polynomial& Polynomial::operator=(Polynomial&& p); // Making it a friend to read other p's data IS NOT NECESSARY
friend Polynomial parabola(double a0, double a1, double a2); // this function however needs to be a friend

public:
    // constructors
    Polynomial(const int& degree); // degree constructor
    Polynomial(const Polynomial& p) = default; // Copy constructor
    Polynomial(std::initializer_list<double> values); //initializer list constructor
    
    // assignments
    Polynomial& operator=(Polynomial&& p); // Move assignment.
    Polynomial& operator=(std::initializer_list<double> values); //initializer list assignment
    
    // destructor
    ~Polynomial() = default; // int's and vectors can be destroyed and release their memory
    
private:    
    int degree;
    std::vector<double> coeffs;
};

Polynomial parabola(double a0, double a1, double a2); //create parabola
std::ostream& operator<< (std::ostream& stream, const Polynomial &rhs); //output
