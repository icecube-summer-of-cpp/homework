// Summer of C++ 
// Homework Week 2 
// Excercise 2.8.1, 2.8.2, 2.8.3 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

/*
 * 2.8.1
 * Write a class for polynomials that should at least contain:
 *      * A constructor giving the degree of the polynomial;
 *      * A dynamic array / vector / list of double to store the coefficients;
 *      * A destructor; and
 *      * A output function for ostream.
 * Further members like arithmetic operations are optional.
 * 
 * 2.8.2 
 * Write a move assignment operator for the polynomial in Exercise 2.8.1. Define the copy constructor as default.
 * To test whether your assignment is used write a function polynomial f(double c2, double c1, double c0) that takes 
 * three coefficients and returns a polynomial. Print out a message in your move assignment or use a debugger to make sure your 
 * assignment is used.
 * 
 * 2.8.3
 * Extend the program from Exercise 2.8.1 with a constructor and an assignment 
 * operator for a initializer list. The degree of the polynomial should be the 
 * length of the initializer list minus one afterward.
 * 
 */

#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <iostream>
#include <sstream>
#include <vector>
#include <initializer_list>
#include <assert.h>
#include <math.h>

class polynomial {
    
    public:
        //members
        int deg;
        std::vector<double> coef;
        
        
        // methods

        // constructor
        polynomial(int degree);
        
        // Define the copy constructor as default.
        polynomial(const polynomial&) = default;    
        
        // move constructor
        // polynomial(polynomial&& src);
        
        // constructor for a initializer list
        polynomial(std::initializer_list<double> values);
        
        // A destructor
        ~polynomial();
        
        // To be consistent in constructor and assignment
        polynomial& operator=(const polynomial&) = default;
        
        // move assignment operator, make a print in here
        polynomial& operator=(polynomial&& src);
        
        // assignment operator for a initializer list
        polynomial& operator=(std::initializer_list<double> values);
        
        // arithmetic methods
        polynomial operator+(const polynomial& p2);
        polynomial operator+=(const polynomial& p2);
        polynomial operator-(const polynomial& p2);
        polynomial operator-=(const polynomial& p2);
        polynomial operator*(const polynomial& p2);
        polynomial operator*=(const polynomial& p2);
        double operator()(const double& x);
};

// outout function for ostream
std::ostream& operator <<(std::ostream& os, const polynomial& p);

polynomial f(double c2, double c1, double c0);

#endif
