/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.10
 * A simple method for computing the integral of a function is the trapezoid
 * rule. Suppose we want to integrate the function f over the interval [a, b].
 * We split the interval in n small intervals [xi, xi+1] of the same length
 * h= (b – a)/n and approximate f by a piecewise linear function. The integral
 * is then approximated by the sum of the integrals of that function.
 * In this exercise, we develop a function for the trapezoid rule, with a
 * functor argument. For comparison, implement this using inheritance and
 * generic programming.
 * As a second exercise, develop a functor for computing the finite difference.
 * Then integrate the finite difference to verify that you get the function
 * value back.
 */


#include <cmath>
#include <iostream>


// template <typename T, typename F>
// class trapezoid
// {
//     public:
//         trapezoid(const F& func, const int& n=1000)
//         : f(func), n(n) {}

//         T operator()(const T& a, const T& b) const
//         {
//             double h = (b-a)/n;
//             T integral = (f(a) * h/2) + (f(b) * h/2);
//             for (int j=1; j<n; j++)
//             {
//                 integral += h * f(a+j*h);
//             }
//             return integral;
//         }

//     private:
//         const F& f;
//         int n;
// };


template <typename T=double, typename F>
T trapezoid(const F& f, const T& a, const T& b, const int& n=1000)
{
    double h = (b-a)/n;
    T integral = (f(a) * h/2) + (f(b) * h/2);
    for (int j=1; j<n; j++)
    {
        integral += h * f(a+j*h);
    }
    return integral;
}



double exp3f(double x) {
        return std::exp(3.0 * x);
}

struct exp3t {
    double operator() (double x) const {
        return std::exp(3.0 * x);
    }
};


struct sinorcos {
    double operator()(double x) const
    {
        if (x<1) {return std::sin(x);}
        else {return std::cos(x);}
    }
};



int main()
{
    std::cout << "Function integral: " <<
    trapezoid(exp3f,0.,4.) << " (54251)" << std::endl;

    exp3t func_obj;
    std::cout << "Struct object integral: " <<
    trapezoid(func_obj,0.,4.,100) << " (54251)" << std::endl;

    sinorcos trig_function;
    std::cout << "Trig integral: " <<
    trapezoid(trig_function,0.,4.) << " (-1.13858)" << std::endl;

    // std::sin is not unique and can't be resolved by the trapezoid template
    // std::cout << "Sin integral: " <<
    // trapezoid(std::sin,0.,2.) << " (1.4161)" << std::endl;
}
