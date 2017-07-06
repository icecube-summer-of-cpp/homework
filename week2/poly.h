#ifndef KEINE_AHNUNG_WAS_DAS_MACHT_POLY
#define KEINE_AHNUNG_WAS_DAS_MACHT_POLY

#include <iostream>
#include <sstream>
#include <vector>
#include <initializer_list>

class polynomial {

    public:
			  int degree;
        std::vector<double> coef;
        polynomial(int degree);      
        polynomial(const polynomial&) = default;    
        polynomial(std::initializer_list<double> values);

        ~polynomial();

        polynomial& operator=(const polynomial&) = default;
        polynomial& operator=(polynomial&& src);
        polynomial& operator=(std::initializer_list<double> values);
        int get_degree();
        std::vector<double> get_coef();
};

polynomial f(double c2, double c1, double c0);

#endif