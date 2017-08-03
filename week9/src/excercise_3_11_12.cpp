// Summer of C++ 
// Quiz Week 9
// Solution by: Rene Reimann

/*
 * 
 * 3.11.12
 * 
 * Lambdas
 * 
 * Compute the same derivative as in Excercise 3.11.11 but this time with a lambda expression.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <memory>
#include <cmath>

template <typename F, typename T, unsigned N>
class nth_derivative{
    using prev_derivative = nth_derivative<F, T, N-1>;
    public:
        nth_derivative(const F& f, const T& h): h(h), fp(f, h) {}
        T operator()(const T& x) const { return (fp(x+h) -fp(x)) /h; };
        
    private:
        T               h;
        prev_derivative fp;
};

template <typename F, typename T>
class nth_derivative<F, T, 1>{
    public:
        nth_derivative(const F& f, const T& h): f(f), h(h) {}
        T operator()(const T& x) const { return (f(x+h) -f(x)) /h; };
        
    private:
        const F& f;
        T        h;
};

template <unsigned N, typename F, typename T>
nth_derivative<F, T, N>
make_nth_derivative(const F& f, const T& h){ return nth_derivative<F, T, N>(f, h); }

int main (int argc, char **argv) 
{
    auto func_o = [](double x){return 2*std::cos(x)+x*x;};
    auto d_func_o = make_nth_derivative<1>(func_o, 0.001);
    auto dd_func_o = make_nth_derivative<2>(func_o, 0.001);
    std::cout << func_o(1.) << std::endl;
    std::cout << d_func_o(1.) << std::endl;
    std::cout << dd_func_o(1.) << std::endl;
    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
