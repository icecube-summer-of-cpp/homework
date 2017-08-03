// Summer of C++ 
// Homework Week 7 
// Solution by: Rene Reimann

/*
 * 
 * 3.11.1
 * 
 * Write a generic function to_string that takes an argument of an arbitrary type (as const&) and generates a string by piping it to as std::stringstream and returning the resulting string.
 * 
 */

#include "sstream"
#include "gtest/gtest.h"

template <typename T>
std::string to_string(const T& obj){
    std::stringstream s;
    s << obj;
    return s.str();
}



int main (int argc, char **argv) 
{
    const int n = 3;
    std::string s = to_string(n);
    std::cout << s << std::endl;
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
}
