// Summer of C++ 
// Quiz Week 9
// Solution by: Rene Reimann

/*
 * 
 * 3.11.10
 * 
 * Trapezoid Rule
 * 
 * A simple method to compute the integral of a function is the trapezoid rule. Suppose
 * we want to integrate the function f over the interval [a, b]. We split the interval in n small 
 * intervals [x_i, x_i+1] of the same length h = (b-a)/n and approximate f by a piecewise linear
 * function. The integral is then approximated by the sum of the integrals of that function.
 * This leads to the following formular:
 * 
 *      I = h/2*f(a) + h/2*f(b) + h sum_{j=1}^{n-1} f(a + jh)
 * 
 * In this exercise, we develop a function for the trapezoid rule, with a functor argument. 
 * For comparison, implement this using inheritance and generic programming. As a test case,
 * integrate:
 * 
 *  * f = exp(-3x) for x in [0,4]. Try trapezoid with the following arguments:
 *      double exp3f(double x){
 *          return std::exp(3.0*x);     
 *      }
 * 
 *      struct exp3t{
 *          double operator() (double x) const {
 *              return std::exp(3.0*x);
 *          }
 *      };
 * 
 *  * f= sin(x) if x < 1 and f = cos(x) if x>=1 for x in [0,4].
 * 
 *  * Can we call trapezoid( std::sin, 0.0, 2.0); ?
 * 
 * As a second exercise, develop a functor for computing the finite difference. Then integrate 
 * the finite difference to verify that you get the function value back.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <memory>
#include <cmath>



struct functor_base{
    public:
        virtual double operator() (double x) const = 0;
};

/*** finit difference ***/

class fin_diff: public functor_base{
    // As a second exercise, develop a functor for computing the finite difference.
    public:
        fin_diff(functor_base const& f, double h): f_(f), h_(h){} 
        
        double operator()(double x) const{
            return (f_(x+h_)-f_(x))/h_;
        }
    private:
        functor_base const& f_;
        double h_;
};

/*** finit difference ***/

double trapezoid(functor_base const& f, double a, double b, int N=1000) {
    // I = h/2*f(a) + h/2*f(b) + h sum_{j=1}^{n-1} f(a + jh)
    double h = (b-a)/N;
    double integral = h/2.*( f(a)+f(b) );
    for (int j=1; j<N; ++j){ integral += h*f(a+j*h); }
    return integral;
}

/***  Functions to test ***/

double exp3f(double x){
     return std::exp(-3.0*x);     
} 

struct exp3t: public functor_base{
    public:
        double operator() (double x) const {
            return std::exp(-3.0*x);
        }
};

double sin_cos(double x){
    return x < 1. ? std::sin(x) : std::cos(x);
};

/*** main ***/

int main (int argc, char **argv) 
{
    //std::cout << trapezoid(exp3f, 0., 4., 100) << std::endl;
    std::cout << trapezoid(exp3t(), 0., 4.) << std::endl;
    //std::cout << trapezoid(sin_cos, 0., 4.) << std::endl;
    //std::cout << trapezoid(std::sin, 0.0, 2.0) << std::endl;
    // note:   couldn't deduce template parameter ‘F’
    
    double upper_bound = 4.;
    double lower_bound = 0.;
    double h_fin_diff = 0.001;
    std::cout << "int_low^up dx df/dx = "<< trapezoid(fin_diff(exp3t(), h_fin_diff), lower_bound, upper_bound) << std::endl;
    std::cout << "int_low^up dx df/dx = "<< trapezoid(fin_diff(exp3t(), h_fin_diff), lower_bound, upper_bound, 10000) << std::endl;
    std::cout << "int_low^up dx df/dx = "<< trapezoid(fin_diff(exp3t(), 0.00001), lower_bound, upper_bound) << std::endl;
    std::cout << "int_low^up dx df/dx = "<< trapezoid(fin_diff(exp3t(), 0.00001), lower_bound, upper_bound, 10000) << std::endl;
    /*
     * int_low^up df/dx dx =  f |_low^up = f(up) - f(low)
     */
    std::cout << "f(up)-f(low) = " << exp3t()(upper_bound) - exp3t()(lower_bound) << std::endl;

    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
