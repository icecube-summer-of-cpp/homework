/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.1
 * Write a generic function to_string that takes an argument of an arbitrary
 * type (as const&) and generates a string by piping it to a std::stringstream
 * and returning the resulting string.
 */
 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


template <typename T>
std::string to_string(T& arg)
{
    std::stringstream stream;
    stream << arg;
    return stream.str();
}


template <typename T>
void check_string(T& arg)
{
    std::string arg_str = to_string(arg);
    std::cout << arg << ": " << arg_str << "   (" << arg_str.length() << ")" << std::endl;
}




struct custom
{
    double x,y,z;
};

std::ostream& operator<<(std::ostream& os, const custom& c)
{
    return os << "(" << c.x << "," << c.y << "," << c.z << ")";
}


int main()
{
    int a = 0;
    check_string(a);

    double b = 3.14159;
    check_string(b);

    std::string s = "Hello world!";
    check_string(s);

    // std::vector<int> v{0,1,2,3,4,5};
    // check_string(v);

    custom c{6,7,8};
    check_string(c);
}