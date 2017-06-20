#include <iostream>
#include <vector>
#include <initializer_list>
#include <assert.h>

class Poly{
  public:
    // Constructor for vector
    Poly(int degree) : deg(degree){
        degree = degree;
        coeff = std::vector<double> (degree + 1);
        for (int i = 0; i < coeff.size(); ++i) {
            coeff[i] = 0.;
        };
      std::cout << "__Degree Constructored__" << std::endl;
    };

    // Getter & Setter
    std::vector<double> get_coeff(){
      return coeff;
    }
    void set_coeff(std::vector<double>& new_coeff){
      for (int i = 0; i < new_coeff.size(); ++i){
        coeff[i] = new_coeff[i];
      };
      std::cout << "__Coeff Setted__" << std::endl;
    }

    int get_degree(){
      return deg;
    }
    void set_degree(int new_deg){
      deg = new_deg;
      coeff = std::vector<double> (deg + 1);
        for (int i = 0; i < coeff.size(); ++i) {
            coeff[i] = 0.;
        };
      std::cout << "__Degree Setted__" << std::endl;
    }

    // Destructor
    ~Poly(){
      std::cout << "__Destructored__" << std::endl;
    };

    // Operator overloads
    // Explicit copy constructor
    Poly(Poly& p){
      deg = p.get_degree();
      coeff = p.get_coeff();
      std::cout << "__Copy constructored__" << std::endl;
    }
    // Move declared as default (does the same as above without the printing)
    // Poly(Poly& p) = default;

    // Move constructor: Move data over to this poly and leave other one empty
    Poly(Poly&& p) : deg(p.get_degree()), coeff(p.get_coeff()){
      p.set_degree(0);
      std::vector<double> v(0);
      p.set_coeff(v);
      std::cout << "__Move constructored__" << std::endl;
    }

    // Move assignment
    Poly& operator=(Poly&& rhs_poly){
      assert(deg == rhs_poly.get_degree());
      deg = rhs_poly.get_degree();
      coeff = rhs_poly.get_coeff();
      std::vector<double> v(0);
      rhs_poly.set_coeff(v);
      std::cout << "__Move assigned__" << std::endl;
      return *this;
    }

    // initializer_list constructor and assignment
    Poly(std::initializer_list<double> new_coeffs){
      std::cout << "__Init list constructored__" << std::endl;
      deg = new_coeffs.size() - 1;
      coeff = new_coeffs;
    }
    Poly& operator=(std::initializer_list<double> new_coeffs){
      std::cout << "__Init list assigned__" << std::endl;
      deg = new_coeffs.size() - 1;
      coeff = new_coeffs;
      return *this;
    }

 private:
     int deg;
     std::vector<double> coeff;
};

// Free functions (why not usable inside class?)
std::ostream& operator<<(std::ostream& os, Poly& poly)
{
  os << poly.get_coeff()[0] << " * x^0";
  for (int i = 1; i < poly.get_degree() + 1; ++i)
  {
    os << " + " << poly.get_coeff()[i] << " * x^" << i;
  };
  return os;
};

// Test polynomial function taking three coeffs (not sure what this shall do,
// just using the move assignment here on return)
Poly f(double c2, double c1, double c0)
{
  Poly temp(3);
  std::vector<double> v{c0, c1, c2};
  temp.set_coeff(v);
  return std::move(temp);
};

// main
int main(int argc, char const *argv[])
{
  // Construct with degree only, coeffs are all 0, edit one and set back to poly
  std::cout << "\n# Part 1: Just create" << std::endl;
  Poly p1(4);
  std::cout << "p1 is: " << p1 << std::endl;
  std::vector<double> v1 = p1.get_coeff();
  v1[1] = 23., v1[0] = -15.;
  p1.set_coeff(v1);
  std::cout << "p1 after set coeff is: " << p1 << std::endl;

  // Copy construct from p1, set new degree, coeff should be larger then
  std::cout << "\n# Part 2: Copy construct" << std::endl;
  Poly p2(p1);
  std::cout << "p2 after copy construction: " << p2 << std::endl;
  std::cout << "p1 after copy construction: " << p1 << std::endl;
  p2.set_degree(2);
  std::cout << "p2 after new degree is set: " << p2 << std::endl;
  std::vector<double> new_coeff{1., 2., 3.};
  p2.set_coeff(new_coeff);
  std::cout << "p2 after coeff is set: " << p2 << std::endl;

  // Move construction
  std::cout << "\n# Part 3: Move construct" << std::endl;
  std::cout << "p2 before move to p3 is: " << p2 << std::endl;
  Poly p3(std::move(p2));
  std::cout << "p2 after move to p3 is: " << p2 << std::endl;
  std::cout << "p3 is: " << p3 << std::endl;

  // Move assignment
  std::cout << "\n# Part 4: Move Assign" << std::endl;
  std::cout << "p3 before move is: " << p3 << std::endl;
  Poly p4 = std::move(p3);
  std::cout << "p3 after move is: " << p3 << std::endl;
  std::cout << "p4 after move is: " << p4 << std::endl;

  // Test polynomial function taking three coeffs
  std::cout << "\n# Part 5: Test f(c2, c1, c0) using move?" << std::endl;
  Poly p5 = f(1., 18., -4.);
  std::cout << "p5 is: " << p5 << std::endl;

  // initializer_list constructored
  std::cout << "\n# Part 6: Construct using initializer_list" << std::endl;
  Poly p6 = {1., 2., 3., 4., 5., 6.};
  std::cout << "p6 is: " << p6 << std::endl;

  // initializer_list assigned
  std::cout << "\n# Part 7: Assign using initializer_list" << std::endl;
  Poly p7(0);
  std::cout << "p7 before assignment is: " << p7 << std::endl;
  p7 = {23., -24., 25.};
  std::cout << "p7 after assignment is: " << p7 << std::endl;

  std::cout << "\n# Last Part: Destructor everything" << std::endl;

  return 0;
}
