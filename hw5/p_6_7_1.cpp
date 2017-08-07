/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 7.6.1
 * Implement the diamond shape from Section 6.3.2 such that the name is only
 * printed once. Distinguish in derived classes between all_info() and
 * my_infos() and call the two functions appropriately.
 */

#include "people.hpp"

int main()
{
    person mark("Mark Markson");
    mark.all_info();

    student tom("Tom Tomson", "Algebra, Analysis");
    tom.all_info();

    mathematician sam("Sam Samson", "Pythagorean Theorem");
    sam.all_info();
    
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();
}