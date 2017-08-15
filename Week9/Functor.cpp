#include <iostream>
#include <math.h>

struct func_f
{
  double operator() (double x) const
  {
    return 2*cos(x) + pow(x,2);
  }
};
  
//old version, not suited for second derivative
/*
template <typename F, typename T>
T fin_diff(F f, const T& x, const T& h)
{
  return (f(x+h) - f(x))/h;
};
*/

template<typename F, typename T>
class derivative
{
  public:
    derivative(const F& f, const T& h) : f(f), h(h) {}

    T operator()(const T& x) const
    {
      return (f(x+h) - f(x) )/h;
    }

  private:
    const F& f;
    T        h;
};

int main()
{
  //std::cout << fin_diff(func_f,1,0.000001) << endl;
  using d_func_f  = derivative<func_f,double>;
  using dd_func_f = derivative<d_func_f,double>;

  func_f    func_o;
  d_func_f  d_func_o(func_o,0.00001);
  dd_func_f dd_func_o(d_func_o,0.00001);

  std::cout << "1st derivatice is: " << d_func_o(1) << "\n" << "2nd derivative is: " << dd_func_o(1) << std::endl;

  return 0;
}
