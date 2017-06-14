#include <cassert>
#include <initializer_list>
#include <iostream>
#include <vector>

struct polynomial
{
    polynomial(unsigned int deg = 0) : coeffs(deg + 1) {}
    polynomial(std::initializer_list<double> cs) : coeffs(cs) {}
    polynomial(const polynomial&) = default;

    ~polynomial()
    {
        std::cout << "This is the destructor." << std::endl;
    }

    polynomial& operator=(polynomial&& other)
    {
        std::cout << "This is the move assignment operator." << std::endl;
        // assigment should not change degree of polynomial
        assert(coeffs.size() == other.coeffs.size());
        std::swap(coeffs, other.coeffs);
        return *this;
    }

    polynomial& operator=(std::initializer_list<double> cs)
    {
        // assigment should not change degree of polynomial
        assert(coeffs.size() == cs.size());
        coeffs.insert(coeffs.end(), cs.begin(), cs.end());
        return *this;
    }

    inline unsigned int degree() const
    {
        return coeffs.size() - 1;
    }

    std::vector<double> coeffs;
};

std::ostream& operator<<(std::ostream& os, const polynomial& po)
{
    for (int i = 0, n = po.degree(); i < n; ++i)
    {
        os << 'c' << n - i << " = " << po.coeffs[i] << ", ";
    }

    os << "c0 = " << po.coeffs.back();

    return os;
}

polynomial parabola(double c2, double c1, double c0)
{
    return polynomial{c2, c1, c0};
}

int main()
{
    polynomial p1(2);
    p1 = parabola(6., 5., 4.);

    std::cout << "Polynomial of degree " << p1.degree()
              << " with coefficients: " << p1 << std::endl;

    polynomial p2 = {3., 2., 1.};

    std::cout << "Polynomial of degree " << p2.degree()
              << " with coefficients: " << p2 << std::endl;
}
