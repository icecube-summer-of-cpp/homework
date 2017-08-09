#include <cmath>
#include <iostream>

template <class F, typename T>
T inline fin_diff(F f, const T& x, const T& h){
  return (f(x+h) - f(x))/h;
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


struct test_functor{
    const double operator()(const double x) const {
      return 2 * std::cos(x) + std::pow(x, 2);
    }
};


int main(){
  auto f0 = test_functor();
  auto f1 = derivative<decltype(f0), double>(f0, 0.001);
  auto f2 = derivative<decltype(f1), double>(f1, 0.001);
  for(unsigned int i = 0; i<10; ++i){
    double x = i;
    std::cout << f0(x) << std::endl;
    std::cout << f1(x) << std::endl;
    std::cout << f2(x) << std::endl;
  }
}