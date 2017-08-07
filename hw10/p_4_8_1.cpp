/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 4.8.1
 * Create a vector of double and initialize it with the values
 * -9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2. You can use an initializer list.
 * Sort the values by magnitude. Write
 *   • A functor and
 *   • A lambda expression for the comparison. Try both solutions.
 */


#include <algorithm>
#include <cmath>
// #include <cstdlib> // May be necessary to avoid ambiguous overload of std::abs(double)
#include <iostream>
#include <vector>


template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v)
{
    os << "(";
    for (int i=0; i<v.size()-1; ++i) {os << v[i] << ", ";}
    os << v.back() << ")";
    return os;
}


class sort_functor
{
    public:
        bool operator()(double x, double y)
        {
            return std::abs(x) < std::abs(y);
        }
};


int main()
{
    std::vector<double> v = {-9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2};
    std::cout << "Initial vector: " << v << std::endl;

    sort_functor sort_function_object;
    std::sort(v.begin(),v.end(),sort_function_object);
    std::cout << "Sorted vector: " << v << std::endl;

    std::sort(v.begin(),v.end());
    std::cout << "Unsorted vector: " << v << std::endl;

    std::sort(v.begin(),v.end(),[](double x, double y){return std::abs(x) < std::abs(y);});
    std::cout << "Sorted vector: " << v << std::endl;
}