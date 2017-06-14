/* Ben Hokanson-Fasig
 * Polynomial class
 */


// Include guard
#ifndef __POLYNOMIAL_HEADER_INCLUDED__
#define __POLYNOMIAL_HEADER_INCLUDED__

#include <vector>
#include <iostream>

class Polynomial
{
    public:
        // Custom default constructor
        Polynomial(std::vector<double> coefficients={0});

        // Constructor when double is passed
        Polynomial(double coefficient) : coeff({coefficient}) {}

        // Default copy constructor
        Polynomial(const Polynomial&) = default;

        // Default move constructor
        Polynomial(Polynomial&&) = default;

        // Default copy assignment
        Polynomial& operator=(const Polynomial&) = default;

        // Custom move assignment
        Polynomial& operator=(Polynomial&& src);

        // Default destructor (vector of coefficients manages itself)
        ~Polynomial() = default;
        
        // Bracket operator for easy access to coefficients
        double operator[](int i) const;

        // Function to return degree of polynomial
        int degree() const;


    // Allow stream output to access private members
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
    
    private:
        std::vector<double> coeff;

        // Function to get index of first non-zero coefficient
        int first_nonzero() const;
};


// Stream output function for polynomial
std::ostream& operator<<(std::ostream& os, const Polynomial& p);


// Function for adding polynomials
Polynomial operator+(const Polynomial& p1, const Polynomial& p2);

// Function for multiplying polynomials
Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

// Function for unary - of polynomials
Polynomial operator-(const Polynomial& p);

// Function for subtracting polynomials
Polynomial operator-(const Polynomial& p1, const Polynomial& p2);

#endif