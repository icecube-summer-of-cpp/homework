#include <vector>
#include <iostream>
#include <cassert>
#include <initializer_list>

class polynomial {
    public:
	// Variables
	unsigned int degree;
	std::vector<double> coeff;
	
	// Functions
	// standard constructor
	polynomial(unsigned int dnew) : degree(dnew), coeff(dnew+1){} 
		
	// standard destructor, vectors and ints have resource management
	~polynomial(){ std::cout << "DESTROYED >:O !!" << std::endl; }; 
	
	// copy constructor is default
	polynomial(const polynomial& p) = default; 
	    
	// this is the move assignment
	polynomial& operator=(polynomial&& psrc){
	    assert(degree == psrc.degree);
	    assert(coeff.size() == psrc.coeff.size());
	    std::swap(degree, psrc.degree);
	    std::swap(coeff, psrc.coeff);
	    std::cout << "Moved the polynomial!" << std::endl;
	    return *this;
	    }
	    
	// Initializer list
	// Constructor
	polynomial(std::initializer_list<double> vals) :
	    degree(vals.size() - 1), coeff(vals.size()){
		std::copy(std::begin(vals), std::end(vals), std::begin(coeff));
		}
	// Assignment
	polynomial& operator=(std::initializer_list<double> vals){
	    assert(coeff.size() == vals.size());
	    std::copy(std::begin(vals), std::end(vals), std::begin(coeff));
	    return *this;
	    }
	
    };

std::ostream& operator<<(std::ostream& os, const polynomial& p){
    os << "Polynom of degree " << p.degree << std::endl;
    for(unsigned int i=0; i<p.coeff.size(); ++i){
	os << p.coeff[i] << " * x^" << i ;
	if (i < p.coeff.size()-1) {os << " + ";}
	}
    os << std::endl;
    }
    
polynomial f(double c0, double c1, double c2){
    polynomial p(2);
    p.coeff= {c0, c1, c2};
    return p;
    }

int main(){
    
    polynomial p(3);
    p.coeff = {1,2,3,4};
    std::cout << p << std::endl;
    
    polynomial p2(p);
    std::cout << p2 << std::endl;
    
    polynomial p3(2);
    p3= f(3,4,6);
    std::cout << p3 << std::endl;
    
    polynomial p4= {1, 0, 1, 2};
    std::cout << p4 << std::endl;
}
