#include <math.h>
#include <iostream>

struct exp3t_f {
  double operator() (double x) const {
    return exp(3.0 * x);
  }
};

struct sincos_f {
  double operator() (double x) const {
    if(x < 1){
      return sin(x);
    }
    else{
      return cos(x);
    }
  }
};

template <typename F, typename T>
class trapezoid
{
  public:
    trapezoid(const F& f, const int& n) : f(f), n(n) {}

    T operator()(const T& a,const T& b) const
    {
      T h = (b - a)/n;
      T sum = 0;
      for(int j=1;j<n;j++){
	sum += f(a+j*h);
      }
      sum *= h;
      return (h/2)*f(a) + (h/2)*f(b) + sum;
    }

  private:
    int      n;
    const F& f;
};

int main()
{
  using trap_exp3t_f = trapezoid<exp3t_f,double>;
  exp3t_f       exp3t_o;
  trap_exp3t_f  trap_exp3t_o(exp3t_o,2000);
  std::cout << "Int. of exp^(3x) [0-4]: " << trap_exp3t_o(0,4) << std::endl;

  using trap_sincos_f = trapezoid<sincos_f,double>;
  sincos_f       sincos_o;
  trap_sincos_f  trap_sincos_o(sincos_o,2000);
  std::cout << "Int. of sin-cos() [0-4]: " << trap_sincos_o(0,4) << std::endl;

  return 0;
}

