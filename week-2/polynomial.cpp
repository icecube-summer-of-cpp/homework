#include "polynomial.hpp"

/* Write a class for polynomials with
 * (2.8.1)
 * a constructor giving the degree of the polynomial                  -> DONE ->
 * a dynamic array/vector/list of double to store the coefficients    -> DONE ->
 * a destructor                                                       -> DONE ->
 * an output function for ostream.                                    -> DONE ->
 * (2.8.2)
 * Write a move assignment operator.
 * Define the copy constructor as default.
 * To test whether your assignment is used write a a function
 * polynomial f(double c2, double c1, double c0) 
 * that takes three coefficients and returns a polynomial. 
 * Print out a message in your move assignment or use a debugger to make sure
 * your assignment is used.
 * (2.8.3)
 * Expand the program with a constructor and an assignment operator for an
 * initializer list. The degree of the polynomial should be the length of the
 * initializer list minus one afterward.
 */
Polynomial::Polynomial(const int& degree) : degree(degree), coeffs(std::vector<double>(degree+1))
{
        for (int i=0; i<degree+1;i++) coeffs[i] = 0;
}
    

std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
    if (p.degree==0) os<<"0";
    else
    {
        os << p.coeffs[0];
        for (int i=1;i<p.degree+1;i++)
        {
            if (p.coeffs[i]>0) os << " + "<<p.coeffs[i]<<"x^"<<i;
            if (p.coeffs[i]<0) os << " - "<< (-p.coeffs[i])<<"x^"<<i;
        }
    }
return os;
}


int main()
{
    Polynomial p(2);
    std::cout << p << std::endl;
}