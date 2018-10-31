/**
 * Solution to exercise 3.11.1
 */
#include <iostream>
#include <string>
#include <sstream>

template<typename T>
std::string to_string(const T& p)
{
    std::ostringstream os;
    os << p;
    return os.str();
}

int main()
{
    std::cout << "to_string(1): " << to_string(1) << std::endl;
}
