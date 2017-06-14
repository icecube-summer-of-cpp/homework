#include "Polynomial.h"

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

polynomial operator+(polynomial& p1,polynomial& p2)
{
  if (p1.degree()<=p2.degree()){
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

polynomial operator-(polynomial& p1,polynomial& p2)
{
  if (p1.degree()<=p2.degree()){
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


int main(){
  vector<double> v = {1.,3,5.,0,-4};
  polynomial p1(v);

  cout << p1 << endl;


  cout << degree(p1) << endl;
  cout << p1.degree() << endl;
  cout << p1[0] << endl;

  cout << p1 << endl;

  polynomial p2({5.,-9.});
  cout << p2 << endl;

  polynomial p3 = p1+p2;

  return 0;
}
