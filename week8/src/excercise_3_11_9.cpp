// Summer of C++ 
// Quiz Week 8 
// Solution by: Rene Reimann

/*
 * 
 * 3.11.9
 * 
 * Deducing Non-type Template Arguments
 * 
 * We have seen that the type of a template argument can be deduced in a function call.
 * Non-type template arguments are in most cases declared explicitly, but they can be deduced
 * as well when they are part of the argument type. As illustration: write a function array_size
 * that accepts a C array of arbitrary type and size as a reference and returns the size of that 
 * array.  The actual function argument can be omitted since we are only interested in its type.
 * Do you remember? We threatened this exercise in Section 1.8.7.1 On the other hand, we 
 * revealed the trickiest part of it in the meantime.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <memory>

template <typename T, int N>
int array_size( T(&)[N] ){
    return N;
};

int main (int argc, char **argv) 
{
    int test[10];
    std::cout << array_size(test) << std::endl;
    float test2[33];
    std::cout << array_size(test2) << std::endl;
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
