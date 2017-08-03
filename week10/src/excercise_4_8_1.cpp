// Summer of C++ 
// Quiz Week 10
// Solution by: Rene Reimann

/*
 * 
 * 4.8.1
 * 
 * Sorting by Magnitude
 * 
 * Create a vector of double and initialize it with the values -9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4,
 * 8.2. You can use an initializer list. Sort the values by magnitude. Write
 *  * A functor and
 *  * A lambda expression for the compariosn.
 * Try both solutions.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct abs_comperator{
    public:
        bool operator()(double x, double y) const{
            return std::abs(x) < std::abs(y);
        };
};

int main (int argc, char **argv) 
{
    std::vector<double> v = {-9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2};
    for (auto i:v){std::cout << i << ", ";}
    std::cout << "\n";
    
    // lambda expression
    std::sort(begin(v), end(v), [](double x, double y){return std::abs(x) < std::abs(y);});
    for (auto i:v){std::cout << i << ", ";}
    std::cout << "\n";
    
    std::vector<double> w = {-9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2};
    for (auto i:w){std::cout << i << ", ";}
    std::cout << "\n";
    
    // lambda expression
    std::sort(begin(w), end(w), abs_comperator());
    for (auto i:w){std::cout << i << ", ";}
    std::cout << "\n";
    
    std::cout << "Test" << std::endl;
    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
