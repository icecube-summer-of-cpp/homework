/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.9
 * We have seen that the type of a template argument can be deduced in a
 * function call. Non-type template arguments are in most cases declared
 * explicitly, but they can be deduced as well when they are part of the
 * argument type. As illustration: write a function array_size that accepts a
 * C array of arbitrary type and size as a reference and returns the size of
 * that array. The actual function argument can be omitted since we are only interested in its type.
 */


#include <iostream>

template <typename T, int N>
int array_size(const T (&array)[N])
{
    return N;
}


int main()
{
    int a[10];
    std::cout << array_size(a) << std::endl;
    bool b[9];
    std::cout << array_size(b) << std::endl;
}