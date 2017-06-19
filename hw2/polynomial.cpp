/* Ben Hokanson-Fasig
 * Polynomial class
 */


#include "polynomial.hpp"


// ==================== Polynomial Class Functions ====================

// Polynomial custom default constructor
Polynomial::Polynomial(std::vector<double> coefficients) : coeff(coefficients)
{
    // Set degree
    deg = this->last_nonzero();

    // Catch if all elements are zero
    if (this->first_nonzero()<0) {
        coeff = {0};
        deg = 0;
    }
}

// Constructor when int and vector are passed
Polynomial::Polynomial(int degree, std::vector<double> coefficients)
{
    if (degree==coefficients.size()-1 && coefficients[degree+1]!=0) {
        deg = degree;
        coeff = coefficients;
    }
    else {
        throw badCoefficients(degree,coefficients.size());
    }
}

// Function to return degree of polynomial
int Polynomial::degree() const
{
    return deg;
}

// Function to get index of first non-zero coefficient
int Polynomial::first_nonzero() const
{
    for (int i=0; i<coeff.size(); ++i) {
        if (coeff[i]!=0) {
            return i;
        }
    }
    return -1;
}

// Function to get index of last non-zero coefficient
int Polynomial::last_nonzero() const
{
    for (int i=coeff.size()-1; i>=0; --i) {
        if (coeff[i]!=0) {
            return i;
        }
    }
    return -1;
}

// ==================== End Class Functions ====================


// ==================== Polynomial Operator Overloads ====================

// Polynomial custom move assignment
Polynomial& Polynomial::operator=(Polynomial&& src)
{
    coeff = src.coeff;
    src.coeff.clear();
    std::cout << "Move assignment activated!\n  Moved polynomial with "
    << coeff.size() << " coefficients.\n  Left source with "
    << src.coeff.size() << " coefficients." << std::endl;
    return *this;
}
        
// Bracket operator for easy access to coefficients
double Polynomial::operator[](int i) const
{
    if (i<=deg) {
        return coeff[i];
    }
    else {
        return 0;
    }
}

// Stream output function for polynomial
std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
    // Quick output for 0th degree polynomial
    if (p.deg==0) {
        return os << p.coeff[0];
    }

    // Longer output for longer polynomials
    int start = p.first_nonzero();
    for (int i=start; i<=p.deg; ++i) {
        if (p.coeff[i]==0) {
            continue;
        }
        else if (i>start) {
            if (p.coeff[i]>0) {
                os << " + ";
            }
            else {
                os << " - ";
            }
        }
        if ((p.coeff[i]!=1 && p.coeff[i]!=-1) || i==0) {
            if (p.coeff[i]>0 || i==start) {
                os << p.coeff[i];
            }
            else {
                os << -p.coeff[i];
            }
        }
        if (i>0) {
            os << "x";
        }
        if (i>1) {
            os << "^" << i;
        }
    }
    return os;
};

// Function for adding polynomials
Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
    int size;
    p1.deg>=p2.deg ? size=p1.deg+1 : size=p2.deg+1;
    std::vector<double> coefficients(size);

    for (int i=0; i<size; ++i) {
        coefficients[i] = p1[i] + p2[i];
    }

    return Polynomial(coefficients);
}

// Function for multiplying polynomials
Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{
    int size = p1.deg+p2.deg+1;
    std::vector<double> coefficients(size);

    for (int i=0; i<=p1.deg; ++i) {
        for (int j=0; j<=p2.deg; ++j) {
            coefficients[i+j] += p1[i]*p2[j];
        }
    }

    return Polynomial(coefficients);
}

// Function for unary - of polynomials
Polynomial operator-(const Polynomial& p)
{
    return -1*p;
}

// Function for subtracting polynomials
Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{
    return p1 + -p2;
}

// ==================== End Operator Overloads ====================


// int main()
// {
//     Polynomial a({-1,2});
//     Polynomial b = {{2,3}};
//     Polynomial c = 2.5;
//     Polynomial d = {{0,0,4,0,0,-5,0,6}};
//     Polynomial e = {{0,1,0,0,0}};
//     Polynomial z = 0;
//     Polynomial z2 = {{0,0}};
//     Polynomial g = a*z;
//     Polynomial h = a-b*-d;
//     std::cout << "a = " << a << std::endl;
//     std::cout << "degree of a = " << a.degree() << std::endl;
//     std::cout << "a[0] = " << a[0] << std::endl;
//     std::cout << "a[1] = " << a[1] << std::endl;
//     std::cout << "a[2] = " << a[2] << std::endl;
//     std::cout << "b = " << b << std::endl;
//     std::cout << "c = " << c << std::endl;
//     std::cout << "d = " << d << std::endl;
//     std::cout << "e = " << e << std::endl;
//     std::cout << "z = " << z << std::endl;
//     std::cout << "degree of z = " << z.degree() << std::endl;
//     std::cout << "z2 = " << z2 << std::endl;
//     std::cout << "degree of z2 = " << z2.degree() << std::endl;
//     std::cout << "a + b = " << a+b << std::endl;
//     std::cout << "a + 2 = " << a+2 << std::endl;
//     std::cout << "a * b = " << a*b << std::endl;
//     std::cout << "a * -2 = " << a*-2 << std::endl;
//     std::cout << "a * z = " << a*z << std::endl;
//     std::cout << "degree of a*z = " << g.degree() << std::endl;
//     std::cout << "-a = " << -a << std::endl;
//     std::cout << "a - b = " << a-b << std::endl;
//     std::cout << "-d = " << -d << std::endl;
//     std::cout << "b * -d = " << b*-d << std::endl;
//     std::cout << "a - b * -d = " << a-b*-d << std::endl;
//     std::cout << "degree of a-b*-d = " << h.degree() << std::endl;
// }