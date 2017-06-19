/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 2.8.1
 * Write a class for polynomials that should at least contain:
 *   A constructor giving the degree of the polynomial;
 *   A dynamic array/vector/list of double to store the coefficients;
 *   A destructor; and
 *   A output function for ostream.
 * Further members like arithmetic operations are optional.
 */
/* This code also provides solutions to...
 * Exercise 2.8.2:
 * Write a move assignment operator for the polynomial in Exercise 2.8.1.
 * Define the copy constructor as default. To test whether your assignment is
 * used write a function polynomial f(double c2, double c1, double c0) that
 * takes three coefficients and returns a polynomial. Print out a message in
 * your move assignment or use a debugger to make sure your assignment is used.
 *
 * Exercise 2.8.3:
 * Expand the program from Exercise 2.8.1 with a constructor and an assignment
 * operator for a initializer list. The degree of the polynomial should be the
 * length of the initializer list minus one afterward.
 */

#include "polynomial.hpp"


// Function for testing move assignment
Polynomial f(double c2, double c1, double c0)
{
    return Polynomial({c0,c1,c2});
}


int main()
{
    Polynomial a({-1,2});
    Polynomial b = {{2,3}};
    Polynomial c = 2.5;
    Polynomial d = {{0,0,4,0,0,-5,0,6}};
    Polynomial e = {{0,1,0,0,0}};
    Polynomial z = 0;
    Polynomial z2 = {{0,0}};
    Polynomial g = a*z;
    Polynomial h = a-b*-d;
    Polynomial i(2,{1,1,2});
    std::cout << "a = " << a << std::endl;
    std::cout << "degree of a = " << a.degree() << std::endl;
    std::cout << "a[0] = " << a[0] << std::endl;
    std::cout << "a[1] = " << a[1] << std::endl;
    std::cout << "a[2] = " << a[2] << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "degree of e = " << e.degree() << std::endl;
    std::cout << "z = " << z << std::endl;
    std::cout << "degree of z = " << z.degree() << std::endl;
    std::cout << "z2 = " << z2 << std::endl;
    std::cout << "degree of z2 = " << z2.degree() << std::endl;
    std::cout << "a + b = " << a+b << std::endl;
    std::cout << "a + 2 = " << a+2 << std::endl;
    std::cout << "a * b = " << a*b << std::endl;
    std::cout << "a * -2 = " << a*-2 << std::endl;
    std::cout << "a * z = " << a*z << std::endl;
    std::cout << "degree of a*z = " << g.degree() << std::endl;
    std::cout << "-a = " << -a << std::endl;
    std::cout << "a - b = " << a-b << std::endl;
    std::cout << "-d = " << -d << std::endl;
    std::cout << "b * -d = " << b*-d << std::endl;
    std::cout << "a - b * -d = " << a-b*-d << std::endl;
    std::cout << "degree of a-b*-d = " << h.degree() << std::endl;

    std::cout << "\nTesting move assignment..." << std::endl;
    Polynomial r;
    r = f(2,1,0);

    std::cout << "r = " << r << std::endl;
    std::cout << "degree of r = " << r.degree() << std::endl;

    std::cout << "i = " << i << std::endl;
    std::cout << "degree of i = " << i.degree() << std::endl;
}