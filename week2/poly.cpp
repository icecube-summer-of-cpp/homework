#include "poly.h"

// A constructor giving the degreeree of the polynomial
polynomial::polynomial(int degree): degree(degree), coef(degree+1){
    std::cout << "constructor(int) with degree: " << degree << std::endl;
};

// constructor for a initializer list
polynomial::polynomial(std::initializer_list<double> values): degree(values.size()-1), coef(values.size()){
    std::copy(std::begin(values), std::end(values), std::begin(coef));
    std::cout << "constructor(initializer_list) with degree: " << degree << std::endl;
};

// A destructor
polynomial::~polynomial(){
    std::cout << "Destructor" << std::endl;
};

std::ostream& operator <<(std::ostream& os, const polynomial& poly){
    std::stringstream str_stream("");
    str_stream << "Degree: " << poly.degree << "\n";
    for (int i = 0; i != poly.coef.size(); i++){
        str_stream << ((i != 0) ? " + "  : "") << poly.coef[i] << " * x^" << i ; 
    }
    return os << str_stream.str();
}

int polynomial::get_degree()
{
    return degree;
};

std::vector<double> polynomial::get_coef()
{
    return coef;
};

polynomial& polynomial::operator=(polynomial&& partner){
    degree = partner.degree;
    coef.resize(degree + 1);
    std::copy(std::begin(partner.coef), std::end(partner.coef), std::begin(coef));
    std::cout << "assigment with different polynomial" << std::endl;
    return *this; 
}

polynomial& polynomial::operator=(std::initializer_list<double> list){
    degree = list.size() - 1;
    coef.resize(degree + 1);
    std::copy(std::begin(list), std::end(list), std::begin(coef));
    std::cout << "assigment initializer list" << std::endl;
    return *this;
}

polynomial f(double coeff_0, double coeff_1, double coeff_2){    
    polynomial p1(2);
    p1.coef[0] = coeff_0;
    p1.coef[1] = coeff_1;
    p1.coef[2] = coeff_2;
    return p1;
};

int main(){   
    polynomial test_poly = f(3., 2., 1.);
    std::cout << test_poly << std::endl;
    polynomial test_poly_1{4., 3., 2., 1.};
    std::cout << test_poly_1 << std::endl;
    test_poly_1 = {1., 2., 3., 4.};
    std::cout << test_poly_1 << std::endl;
    polynomial test_poly_2 = test_poly;
    std::cout << test_poly_2 << std::endl;

    return 0;
}