#include <iostream>
#include <cmath>


double exp3f(double x) {
  return std::exp(3.0 * x);
}

struct exp3t {
    double operator()(double x) const {
      return std::exp(3.0 * x);
    }
};

double sin_cos(double x){
  if(x<1){
    return std::sin(x);
  }else{
    return std::cos(x);
  }
}


template <typename F, typename T>
const T trapezoid(const F& f, const T& a, const T& b, const unsigned N=0){
  T h = (b-a)/(N+1);
  T res = h/2*(f(b)+f(a));
  for(unsigned int i= 1; i<N; ++i){
    res += h * f(a + i * h);
  }
  return res;
};

template <class F, typename T>
class derivative{
    const F& f;
    T h;
public:
    derivative(const F& f, const T& h): f(f), h(h) {}
    
    T operator()(const T& x) const {
      return (f(x+h) - f(x))/h;
    }
};


int main(){
  auto n = 10000000;
  auto x = 1.4;
  auto m = 1000.0;
  auto h = 0.0001;
  std::cout << trapezoid(exp3f, 0., 4., n) << std::endl;
  std::cout << trapezoid(exp3t(), 0., 4., n) << std::endl;
  std::cout << trapezoid(sin_cos, 0., 4., n) << std::endl;
  std::cout << trapezoid<double (double), double >(std::sin, 0., 4., n) << std::endl;
  std::cout << "------------------------------" << std::endl;
  auto d0 = derivative<decltype(exp3f), double>(exp3f, h);
  auto d1 = derivative<decltype(exp3t()), double>(exp3t(), h);
  auto d2 = derivative<decltype(sin_cos), double>(sin_cos, h);
  auto d3 = derivative<double (double), double>(std::sin, h);
  
  std::cout << exp3f(x) << std::endl;
  std::cout << exp3t()(x) << std::endl;
  std::cout << sin_cos(x) << std::endl;
  std::cout << std::sin(x) << std::endl;
  std::cout << "------------------------------" << std::endl;
  
  
  std::cout << trapezoid(d0, x-m, x+m, n) << std::endl;
  std::cout << trapezoid(d1, x-m, x+m, n) << std::endl;
  std::cout << trapezoid(d2, x-m, x+m, n) << std::endl;
  std::cout << trapezoid(d3, x-m, x+m, n) << std::endl;
  
  return 0;
  
}