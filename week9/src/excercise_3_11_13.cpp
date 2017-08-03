// Summer of C++ 
// Quiz Week 9 
// Solution by: Rene Reimann

/*
 * 
 * 3.11.13
 * 
 * Implement `make_unique`
 * 
 * Implement your own `make_unique`. Use `std::forward` to pass parameter packs to the `new`.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <memory>

template <typename T, typename ...P>
std::unique_ptr<T> make_unique(P ...p){ 
    T* temp = new T(p...);
    std::unique_ptr<T> ptr(temp);
    return ptr;
    };

int main (int argc, char **argv) 
{
    int a = 3;
    auto test = make_unique<int>(3);
    test = make_unique<int>(7);
    std::cout << *test << std::endl;
    std::cout << "Test" << std::endl;
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
