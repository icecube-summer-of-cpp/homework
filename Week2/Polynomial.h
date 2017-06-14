#ifndef POLYNOM_H
#define POLYNOM_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <initializer_list>
#include <algorithm>

using namespace std;

class polynomial
{
  public:
    polynomial(vector<double> that);
    
    polynomial(initializer_list<double> values);

    polynomial(const polynomial& x): my_degree(x.my_degree),v(x.v) {}

    polynomial() : my_degree(1),v(vector<double>{0.}) {}
    
    //move constructor
    polynomial(polynomial&& p);

    //move assignment
    polynomial& operator=(polynomial&& p);
    
    ~polynomial() { v.clear() ;}

    int degree() const {return my_degree;}
    vector<double> getvector() const {return v;}
    void set(int i,double value){v[i] = value;}

    const double& operator[](int i) const {
      assert((i>=0) && (i<my_degree) && (v.size()==my_degree));
      return v[i];
    }
 
    friend int const& degree(const polynomial& p){return p.my_degree;};
    friend ostream& operator<<(ostream& ,const polynomial&);
    friend polynomial operator+(const polynomial&, const polynomial&);
    friend polynomial operator-(const polynomial&, const polynomial&);
    //if I have time I'll add the * and / operators

  private:
    int            my_degree;
    vector<double> v;
};


#endif// POLYNOM_H
