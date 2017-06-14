#include "Polynomial.h"

polynomial::polynomial(vector<double> that) : my_degree(that.size()), v(that.size())
{
  for (int i=0;i<my_degree;i++){v[i] = that[i];}
  cout << "Size of the polynomial: " << that.size() << endl;
}

polynomial::polynomial(initializer_list<double> values) : my_degree(values.size()),v(values.size())
{
  copy(begin(values),end(values),begin(v));
}
    
polynomial::polynomial(polynomial&& p): my_degree(p.my_degree),v(p.v)
{
  p.my_degree = 1;
  (p.v).clear() ;
}
 

polynomial& polynomial::operator=(polynomial&& p)
{
  cout << "Using the move assignment" << endl;
  assert(my_degree == 1 || my_degree == p.my_degree);
  swap(my_degree,p.my_degree);
  swap(v,p.v);
  return *this;
}

ostream& operator<<(ostream& os,const polynomial& p)
{
  os << "Polynomial is: ";
  os << p[0];
  for(int i=1;i<degree(p);i++){
    if (p[i]<0){
      os << p[i] << "*x^" << i;
    }
    else if(p[i] !=0)
    {
      os << "+" << p[i] << "*x^" << i;
    }
  }
  os << endl;
  return os;

}

polynomial operator+(const polynomial& p1,const polynomial& p2)
{
  if (p1.degree()>=p2.degree()){
    polynomial maxpol(p1);
    polynomial minpol(p2);

    for(int i=0;i<minpol.degree();i++)
    {
        maxpol.set(i,p1[i] + p2[i]);
    }
    return maxpol;
  }
  else{
    polynomial maxpol(p2);
    polynomial minpol(p1);

    for(int i=0;i<minpol.degree();i++)
    {
        maxpol.set(i,p1[i] + p2[i]);
    }
    return maxpol;
  }
}

polynomial operator-(const polynomial& p1,const polynomial& p2)
{
  if (p1.degree()>=p2.degree()){
    polynomial maxpol(p1);
    polynomial minpol(p2);

    for(int i=0;i<minpol.degree();i++)
    {
        maxpol.set(i,p1[i] - p2[i]);
    }
    return maxpol;
  }
  else{
    polynomial maxpol(p2);
    polynomial minpol(p1);

    for(int i=0;i<minpol.degree();i++)
    {
        maxpol.set(i,p1[i] - p2[i]);
    }
    return maxpol;
  }
}
    
polynomial f(double c2, double c1, double c0){
  polynomial temp({c0,c1,c2});
  return temp;
}

