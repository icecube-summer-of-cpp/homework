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
  vector<double> sum(max(p1.degree(),p1.degree()));
  for(int i=0;i<min(p1.degree(),p2.degree());i++)
  {
    sum[i] = p1[i] + p2[i];
  }
  return polynomial(sum);   
}

polynomial operator-(polynomial& p1,polynomial& p2)
{
  vector<double> sum(max(p1.degree(),p1.degree()));
  for(int i=0;i<min(p1.degree(),p2.degree());i++)
  {
    sum[i] = p1[i] - p2[i];
  }
  return polynomial(sum);   
}

int main(){
  vector<double> v = {1.,3,5.,0,-4};
  polynomial p1(v);

  cout << p1 << endl;

  cout << p4 << endl;


  cout << degree(p1) << endl;
  cout << p1.degree() << endl;
  cout << p1[0] << endl;

  cout << p1 << endl;

  cout << p4 << endl;


  polynomial p5({5.,-9.});
  cout << p5 << endl;

  return 0;
}
