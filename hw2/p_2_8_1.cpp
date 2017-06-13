/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 2.8.1
 * Write a class for polynomials that should at least contain:
 *   A constructor giving the degree of the polynomial;
 *   A dynamic array/vector/list of double to store the coefficients;
 *   A destructor; and
 *   A output function for ostream.
 * Further members like arithmetic operations are optional.
 */

#include <vector>
#include <iostream>

class polynomial
{
    public:
        // Default constructor
        polynomial(std::vector<double> coefficients={0}) : coeff(coefficients)
        {
            // Catch if all elements are zero
            if (this->first_nonzero()<0) {
                coeff = {0};
            }
        }

        // Constructor when double is passed
        polynomial(double coefficient) : coeff({coefficient}) {}

        // Destructor not necessary, vector of coefficients manages itself
        // ~polynomial() {}

        // Function to return degree of polynomial
        int degree() const
        {
            return coeff.size()-1;
        }

        // Bracket operator for easy access to coefficients
        double operator[](int i) const
        {
            if (i<coeff.size()) {
                return coeff[i];
            }
            else {
                return 0;
            }
        }

    // Allow stream output to access private members
    friend std::ostream& operator<<(std::ostream& os, const polynomial& p);

    // Allow aritmentic operations to access private members
    friend polynomial operator+(const polynomial& p1, const polynomial& p2);
    
    private:
        std::vector<double> coeff;

        int first_nonzero() const
        {
            for (int i=0; i<coeff.size(); ++i) {
                if (coeff[i]!=0) {
                    return i;
                }
            }
            return -1;
        }
};


// Stream output function for polynomial
std::ostream& operator<<(std::ostream& os, const polynomial& p)
{
    // Quick output for 0th degree polynomial
    if (p.degree()==0) {
        return os << p.coeff[0];
    }

    // Longer output for longer polynomials
    int start = p.first_nonzero();
    for (int i=start; i<p.coeff.size(); ++i) {
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
            if (p.coeff[i]>0 || i==0) {
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
inline polynomial operator+(const polynomial& p1, const polynomial& p2)
{
    int size;
    p1.degree()>=p2.degree() ? size=p1.degree()+1 : size=p2.degree()+1;
    std::vector<double> coefficients(size);

    for (int i=0; i<size; ++i) {
        coefficients[i] = p1[i] + p2[i];
    }

    return polynomial(coefficients);
}


int main()
{
    polynomial a({-1,2});
    polynomial b = {{2,3}};
    polynomial c = 2.5;
    polynomial d = {{0,0,4,0,0,-5,0,6}};
    polynomial e = {{0,1,0,0,0}};
    polynomial z = 0;
    polynomial z2 = {{0,0}};
    std::cout << "a = " << a << std::endl;
    std::cout << "a[0] = " << a[0] << std::endl;
    std::cout << "a[1] = " << a[1] << std::endl;
    std::cout << "a[2] = " << a[2] << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "z = " << z << std::endl;
    std::cout << "z2 = " << z2 << std::endl;
    std::cout << "a + b = " << a+b << std::endl;
    std::cout << "a + 2 = " << a+2 << std::endl;
}