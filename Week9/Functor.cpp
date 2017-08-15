#include <iostream>
#include <math.h>

struct func_f
{
  double operator() (double x) const
  {
    return 2*cos(x) + pow(x,2);
  }
};
  
template <typename F, typename T>
T fin_diff(F f, const T& x, const T& h)
{
  return (f(x+h) - f(x))/h;
};

int main()
{
  std::cout << fin_diff(func_f,1,0.000001) << endl;
  func_f func_o;
  
  return 0;
}
