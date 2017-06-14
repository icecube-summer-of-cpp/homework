#include "Polynomial.cpp"

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
  
  //polynomial p4;
  //p4= f(99.,88,77);
  //cout << p4 << endl;

  polynomial p5;
  cout << p5 << endl;
 
  return 0;
}

