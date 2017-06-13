//
// Created by Frederik Lauber on 09.06.17.
//

#ifndef CPPSUMMER_POLYNOM_H
#define CPPSUMMER_POLYNOM_H
#include <vector>
#include <iostream>
#include <boost/serialization/strong_typedef.hpp>
#include <memory>

class Polynom {
    std::vector<double> coeff;
    friend std::ostream& operator<< (std::ostream& stream, const Polynom &rhs);
    friend Polynom operator << (Polynom const &lhs, unsigned long shift);
    friend Polynom operator >> (Polynom const &lhs, unsigned int shift);
    friend Polynom operator*(Polynom const& lhs, double const &rhs);
    friend Polynom operator+(Polynom const& lhs, Polynom const& rhs);
    friend Polynom operator+(Polynom const& lhs, double const &rhs);
    friend Polynom operator*(Polynom const& lhs, Polynom const& rhs);
    friend Polynom pow(Polynom const& lhs, unsigned long const& rhs);
    friend double eval(Polynom const& pol, const double& x);
    friend Polynom eval(Polynom const& pol, Polynom const& x);
    
public:
    Polynom(std::vector<double> x) : coeff({x}) {};
    Polynom(std::initializer_list<double> x) : coeff({x}) {};
    unsigned long order();
};

std::ostream& operator<< (std::ostream& stream, const Polynom &rhs);
Polynom operator << (Polynom const &lhs, unsigned long shift);
Polynom operator >> (Polynom const &lhs, unsigned int shift);
Polynom operator*(Polynom const& lhs, double const &rhs);
Polynom operator+(Polynom const& lhs, Polynom const& rhs);
Polynom operator+(Polynom const& lhs, double const &rhs);
Polynom operator*(Polynom const& lhs, Polynom const& rhs);
Polynom pow(Polynom const& lhs, unsigned long const& rhs);
double eval(Polynom const& pol, const double& x);
Polynom eval(Polynom const& pol, Polynom const& x);

#endif //CPPSUMMER_POLYNOM_H
