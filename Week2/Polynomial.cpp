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


int main(){
  vector<double> v = {1.,3,5.,0,-4};
  polynomial p1(v);

  cout << p1 << endl;


  cout << degree(p1) << endl;
  cout << p1.degree() << endl;
  cout << p1[0] << endl;

  cout << p1 << endl;

  polynomial p2({5.,0,-9.});
  cout << p2 << endl;

  polynomial p3 = p1+p2;
  cout << p3 << endl;
  
  polynomial p4;
  p4= f(99.,88,77);
  cout << p4 << endl;

  polynomial p5;
  cout << p5 << endl;

  return 0;
}
