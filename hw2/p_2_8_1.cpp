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
        polynomial(std::vector<double> coefficients={0}) : coeff(coefficients) {}

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
};


// Stream output function for polynomial
std::ostream& operator<<(std::ostream& os, const polynomial& p)
{
    // Quick output for 0th degree polynomial
    if (p.degree()==0) {
        return os << p.coeff[0];
    }

    // Longer output for longer polynomials
    for (int i=0; i<p.coeff.size(); ++i) {
        if (p.coeff[i]==0) {
            continue;
        }
        if (i>0) {
            os << " + ";
        }
        os << p.coeff[i];
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
    polynomial a({1});
    polynomial b = {{2,3}};
    polynomial d = {{4,0,5,6}};
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << d << std::endl;
}