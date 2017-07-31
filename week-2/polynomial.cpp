#include "polynomial.hpp"

/* Write a class for polynomials with
 * (2.8.1)
 * a constructor giving the degree of the polynomial                  -> DONE ->
 * a dynamic array/vector/list of double to store the coefficients    -> DONE ->
 * a destructor                                                       -> DONE ->
 * an output function for ostream.                                    -> DONE ->
 * (2.8.2)
 * Write a move assignment operator.                                  -> DONE ->
 * Define the copy constructor as default.                            -> DONE ->
 * To test whether your assignment is used write a a function
 * polynomial f(double c2, double c1, double c0) 
 * that takes three coefficients and returns a polynomial.            -> DONE ->
 * Print out a message in your move assignment or use a debugger to make sure
 * your assignment is used.                                           -> DONE ->   
 * (2.8.3)
 * Expand the program with
 * a constructor and
 * an assignment operator
 * for an initializer list. The degree of the polynomial should be the length of the
 * initializer list minus one afterward.
 */
 
 // degree constructor
Polynomial::Polynomial(const int& degree) : degree(degree), coeffs(std::vector<double>(degree+1, 0.)) {}

// initializer list constructor
Polynomial::Polynomial(std::initializer_list<double> values)
    : degree(values.size()-1), coeffs(std::vector<double>(values.size(),0.))
{
    std::copy(std::begin(values),std::end(values),
              std::begin(coeffs));
}

// move assignment
Polynomial& Polynomial::operator=(Polynomial&& p)
{
    assert (degree == p.degree);
    std::swap(coeffs,p.coeffs);
    std::cout << "I like to move it move it" << std::endl;
    return *this;
}

//  initializer_list assignment
Polynomial& Polynomial::operator=(std::initializer_list<double> values)
{
    //assert (degree == values.size()); // not needed for the Polynomial concept
    degree = values.size()-1;
    coeffs = std::vector<double>(values.size(),0.);
    std::copy(std::begin(values),std::end(values),
              std::begin(coeffs));
    return *this;
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

Polynomial parabola(double a0, double a1, double a2)
{
    Polynomial p(2);
    p.coeffs[0] = a0;
    p.coeffs[1] = a1;
    p.coeffs[2] = a2;
    return p;
}

int main()
{
    // degree constuctor
    Polynomial p1(2);
    Polynomial p2(2);
    
    // output of 0 parabola
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    
    std::cout<< "First assignment p2 = parabola(1.,2.0,0.5);" << std::endl;
    p2 = parabola(1.,2.0,0.5); // triggers the move operator
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout<< "Second assignment p1 = std::move(p2);" << std::endl;
    p1 = std::move(p2); // moves explicitly
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    
    std::cout<< "initializer_list constructor p3{1., 2., 3.};" << std::endl;
    Polynomial p3{1., 2., 3}; // initializer_list constructor
    std::cout << p3 << std::endl;
    Polynomial p4(2);
    std::cout<< "initializer_list assignment without changing degree, p4 = {4., 5., 6.};" << std::endl;
    p4 = {4., 5., 6.}; // initializer_list assignment
    std::cout << p4 << std::endl;
    std::cout<< "initializer_list assignment while changing degree, p4 = {4., 5., 6., 7.};" << std::endl;
    p4 = {4., 5., 6., 7.}; // initializer_list assignment
    std::cout << p4 << std::endl;
    
    
}