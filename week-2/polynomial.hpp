#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

class Polynomial
{   
public:
    Polynomial(const int& degree);
    Polynomial(const Polynomial& p) = default; // Copy constructor
    ~Polynomial() = default;
    
private:
    friend std::ostream& operator<< (std::ostream& stream, const Polynomial& p);
    int degree;
    std::vector<double> coeffs;
};

std::ostream& operator<< (std::ostream& stream, const Polynomial &rhs);