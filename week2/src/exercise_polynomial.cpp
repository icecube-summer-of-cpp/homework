// Summer of C++ 
// Homework Week 2 
// Excercise 2.8.1, 2.8.2, 2.8.3 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

/*
 * 2.8.1
 * Write a class for polynomials that should at least contain:
 *      * A constructor giving the degree of the polynomial;
 *      * A dynamic array / vector / list of double to store the coefficients;
 *      * A destructor; and
 *      * A output function for ostream.
 * Further members like arithmetic operations are optional.
 * 
 * 2.8.2 
 * Write a move assignment operator for the polynomial in Exercise 2.8.1. Define the copy constructor as default.
 * To test whether your assignment is used write a function polynomial f(double c2, double c1, double c0) that takes 
 * three coefficients and returns a polynomial. Print out a message in your move assignment or use a debugger to make sure your 
 * assignment is used.
 * 
 * 2.8.3
 * Extend the program from Exercise 2.8.1 with a constructor and an assignment 
 * operator for a initializer list. The degree of the polynomial should be the 
 * length of the initializer list minus one afterward.
 * 
 */

#include "exercise_polynomial.hpp"

// A constructor giving the degree of the polynomial
polynomial::polynomial(int degree): deg(degree), coef(degree+1){
    std::cout << "create polynomial of degree " << degree << std::endl;
};

// constructor for a initializer list
polynomial::polynomial(std::initializer_list<double> values): deg(values.size()-1), coef(values.size()){
    std::copy(std::begin(values), std::end(values), std::begin(coef));
    std::cout << "create polynomial by initializer list" << std::endl;
};

// A destructor
polynomial::~polynomial(){
    std::cout << "We are in the destructor and cleaned up everything" << std::endl;
};

// move assignment operator, make a print in here
polynomial& polynomial::operator=(polynomial&& src){
    deg = src.deg;
    coef.resize(deg+1);
    std::copy(std::begin(src.coef), std::end(src.coef), std::begin(coef));
    std::cout << "We used the move assignment" << std::endl;
    return *this; 
}

// assignment operator for a initializer list
polynomial& polynomial::operator=(std::initializer_list<double> values){
    deg = values.size()-1;
    coef.resize(deg+1);
    std::copy(std::begin(values), std::end(values), std::begin(coef));
    std::cout << "we used assignment by initializer list" << std::endl;
    return *this;
}
    
// arithmetic methods
polynomial polynomial::operator+(const polynomial& p2){
    std::cout << "We try to add things together" << std::endl;
    auto temp = coef;
    deg = temp.size() < p2.coef.size() ? p2.coef.size()-1 : temp.size()-1;
    coef.resize(deg+1);
    for(int i=0; i<=deg; i++){
        if (i < temp.size() && i < p2.coef.size()){ coef[i] = temp[i] + p2.coef[i]; } 
        else{ coef[i] = (i >= temp.size()) ? p2.coef[i] : temp[i]; }
    }
    return *this;
};

polynomial polynomial::operator+=(const polynomial& p2){
    std::cout << "We try to add things together and assigne them directly" << std::endl; 
    return *this + p2;
};

polynomial polynomial::operator-(const polynomial& p2){
    std::cout << "We try to substract things" << std::endl;
    auto temp = coef;
    deg = temp.size() < p2.coef.size() ? p2.coef.size()-1 : temp.size()-1;
    coef.resize(deg+1);
    for(int i=0; i<=deg; i++){
        if (i < temp.size() && i < p2.coef.size()){ coef[i] = temp[i] - p2.coef[i]; } 
        else{ coef[i] = (i >= temp.size()) ? -p2.coef[i] : temp[i]; }
    }
    return *this;
};

polynomial polynomial::operator-=(const polynomial& p2){
    std::cout << "We try to substract things and assigne them directly" << std::endl; 
    return *this - p2;
};

polynomial polynomial::operator*(const polynomial& p2){
    std::cout << "We try to multiply things together" << std::endl;
    auto c1 = coef;
    auto c2 = p2.coef;
    deg = (c1.size()-1) + (c2.size()-1);
    coef.resize(deg+1);
    for(int i=0; i<=deg; i++){ coef[i] = 0;}
    for(int i=0; i<c1.size(); i++){
        for(int j=0; j<c2.size(); j++){
            std::cout << "i, j: " << i << " " << j << ", coef[i+j]: " << coef[i+j] << ", c1[i], c2[j]: " << c1[i] << " " << c2[j] << std::endl;  
            coef[i+j] += c1[i] * c2[j];
        }
    }
    return *this;
};

polynomial polynomial::operator*=(const polynomial& p2){
    std::cout << "We try to multiply things and assigne them directly" << std::endl; 
    return (*this) * p2;
};

double polynomial::operator()(const double& x){
    double sum = 0;
    for (int i=0; i<=deg; i++){
        sum += coef[i]*pow(x, i);
    }
    return sum;
};

std::ostream& operator <<(std::ostream& os, const polynomial& p){
    std::stringstream s("");
    s << "Polynome if size " << p.coef.size() << " " << p.deg << ": " ;
    for (int i = 0; i != p.coef.size(); i++){
        s << ((i!=0) ? " + "  : "") << p.coef[i] << "*x^" << i ; 
    }
    return os << s.str();
}

polynomial f(double c2, double c1, double c0){    
    polynomial p1(2);
    p1.coef[0] = c2;
    p1.coef[1] = c1;
    p1.coef[2] = c0;
    return p1;
};

int main(int argc, char* argv[]){
    
    // to test if everything works we have a print out in each constructor, assignment and operator
    // thus we see if the expected function is called, to check if the function does the right thing 
    // we print the polynomial after each interaction
    
    polynomial p1 = polynomial(3);
    std::cout << p1 << std::endl;
    p1 = f(1., 2., 3.);
    std::cout << p1 << std::endl;
    
    polynomial p2{1.0, 4.5, 3.3, 7.6};
    std::cout << p2 << std::endl;
    
    p2 = {2.0, 9.0, 6.6, 15.2};
    std::cout << p2 << std::endl;
    
    p1 = p2;
    std::cout << p1 << std::endl;
    
    p1 = f(4.,3.3, -8.0);
    std::cout << p1 << std::endl;
    
    polynomial p3 = f(3., 2., 1.) + polynomial{5., 4., 3., 2., 1};
    std::cout << p3 << std::endl;
    
    p3 += f(1., 1., 1.);
    std::cout << p3 << std::endl;

    p3 -= f(10., 20., 30.);
    std::cout << p3 << std::endl;
    
    p3 += {5.};
    std::cout << p3 << std::endl;
    
    p3 *= {1.};
    std::cout << p3 << std::endl;
    
    p3 *= {1., 1., 1.};
    std::cout << p3 << std::endl;
    
    polynomial p4 = {1., 1., 1.};
    std::cout << p4 << std::endl;
    
    polynomial p5 = {1., 1., 1.};
    std::cout << p5 << std::endl;
    
    p4 *= p5;
    std::cout << p4 << std::endl;
    
    p5 *= p5;
    std::cout << p5 << std::endl;
    
    std::cout << p5(1.) << std::endl;
    
    return 0;
}
