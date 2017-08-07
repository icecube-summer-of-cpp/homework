/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.11 & Exercise 3.11.12
 * Write a functor for 2 cos x + x^2 and compute the first and second
 * derivatives with the functor from Section 3.8.1.
 * Compute the same derivatives as in Exercise 3.11.11 but this time with a
 * lambda expression.
 */


#include <cmath>
#include <iostream>

template <typename F, typename T>
class derivative
{
    public:
        derivative(const F& f, const T& h) : f(f), h(h) {}
        T operator()(const T& x) const {return (f(x+h)-f(x))/h;}
    private:
        const F& f;
        T h;
};


struct my_functor
{
    double operator()(const double& x) const {return 2*std::cos(x) + x*x;}
};

int main()
{
    std::cout << "With functor:" << std::endl;
    my_functor ff;
    std::cout << "f(0) = " << ff(0) << std::endl;
    derivative<my_functor,double> d_ff(ff,.0001);
    std::cout << "df/dx(0) = " << d_ff(0) << std::endl;
    derivative<derivative<my_functor,double>,double> dd_ff(d_ff,.0001);
    std::cout << "df2/d2x(0) = " << dd_ff(0) << std::endl;

    std::cout << "\nWith lambda:" << std::endl;
    auto lf = [](double x){return 2*std::cos(x) + x*x;};
    std::cout << "f(0) = " << lf(0) << std::endl;
    derivative<decltype(lf),double> d_lf(lf,.0001);
    std::cout << "df/dx(0) = " << d_lf(0) << std::endl;
    derivative<decltype(d_lf),double> dd_lf(d_lf,.0001);
    std::cout << "df2/d2x(0) = " << dd_lf(0) << std::endl;
}