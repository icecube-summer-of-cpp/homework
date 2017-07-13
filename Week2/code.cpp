#include "Polynomial.cpp"

int main(){
  vector<double> v = {1.,3,5.,0,-4};
  polynomial p1(v);

  cout << "p1:" << p1 << endl;

  cout << "Degree of p1 is: " <<degree(p1) << endl;
  cout << "Other function for degree: " << p1.degree() << endl;
  cout << "First argument of p1: " << p1[0] << endl;

  polynomial p2({5.,0,-9.});
  cout << "Now using initializer list" << endl;
  cout << "p2:" << p2 << endl;

  polynomial p3 = p1+p2;
  cout << "Let's see if we can sum p1 and p2" << endl;
  cout << "p3:" << p3 << endl;
  
  polynomial p4;
  p4= f(99.,88,77);
  cout << "Using move assignment (should tell you this if this is true)" << endl;
  cout << p4 << endl;

  polynomial p5;
  cout << "Let's see what the default operator does: " << endl;
  cout << "p5:" << p5 << endl;

  polynomial p6 = p3*p2;
  cout << "We should be able to multiply polynomials: " << endl;
  cout << "p2*p3=p6:" << p6 << endl;

  cout << "Or just with a simple double: " << endl;
  cout << "3*p6" << p6 * 3<<endl;
  return 0;
}

