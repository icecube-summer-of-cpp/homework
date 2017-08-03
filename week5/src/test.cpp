// Summer of C++ 
// Homework Week 5 
// Solution by: Rene Reimann

/*
 * Non-redundant Diamond shape
 * 
 * Implement the Diamond shape from Section 6.3.2 such that the name is only printed once.
 * Distinguish in derived classes between all_info() and my_info() and call the two functions appropriately.
 */

#include "person.hpp" 

int main () 
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();

    return 0 ;
}
