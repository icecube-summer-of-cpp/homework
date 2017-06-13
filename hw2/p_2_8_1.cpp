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

    // Allow stream output to access private members
    friend std::ostream& operator<<(std::ostream& os, const polynomial& p);
    
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
            os << " + ";
        }
        if (p.coeff[i]!=1 || i==0) {
            os << p.coeff[i];
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



int main()
{
    polynomial a({1,2});
    polynomial b = {{2,3}};
    polynomial c = 2.5;
    polynomial d = {{0,0,4,0,0,5,0,6}};
    polynomial e = {{0,1,0,0,0}};
    polynomial z = 0;
    polynomial z2 = {{0,0}};
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "z = " << z << std::endl;
    std::cout << "z2 = " << z2 << std::endl;
}