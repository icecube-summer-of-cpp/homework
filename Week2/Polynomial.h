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
    polynomial(vector<double> that) : my_degree(that.size()), v(that.size())
    {
      for (int i=0;i<my_degree;i++){v[i] = that[i];}
      cout << "Size of the polynomial: " << that.size() << endl;
    }
    polynomial(initializer_list<double> values) :
      my_degree(values.size()),v(values.size())
    {
      copy(begin(values),end(values),begin(v));
    }
    polynomial(polynomial& x): my_degree(x.my_degree),v(x.v) {}

    polynomial() : my_degree(0),v(0) {};
    
    
    /*
    polynomial(polynomial&& p): my_degree(p.my_degree),v(p.v)
    {
      p.my_degree = 0.;
      (p.v).clear() ;
    }
    */ 
   
   /* 
    polynomial& operator=(polynomial&& themove)
    {
      assert(my_degree == 0 || my_degree == themove.my_degree);
      swap(v,themove.v);
      return *this;
    }
    */
    
    ~polynomial() { v.clear() ;}

    int degree() const {return my_degree;}
    vector<double> getvector() const {return v;}
    void set(int i,double value){v[i] = value;}

    const double& operator[](int i) const {
      assert((i>=0) && (i<my_degree) && (v.size()==my_degree));
      return v[i];
    }
  
    polynomial operator=(const polynomial &that)
    {
      my_degree = that.my_degree;
      v = that.v;
      return *this;
    }
    
    friend int const& degree(const polynomial& p){return p.my_degree;};
    friend ostream& operator<<(ostream& ,const polynomial&);
    friend polynomial operator+(polynomial&, polynomial&);
    friend polynomial operator-(polynomial&, polynomial&);
    //if I have time I'll add the * and / operators

  private:
    int            my_degree;
    vector<double> v;
};



