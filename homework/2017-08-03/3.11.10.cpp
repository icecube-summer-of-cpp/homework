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


int main(){
  std::cout << trapezoid(exp3f, 0., 4., 1000) << std::endl;
  std::cout << trapezoid(exp3t(), 0., 4., 1000) << std::endl;
  std::cout << trapezoid(sin_cos, 0., 4., 1000) << std::endl;
  //std::cout << trapezoid(std::sin, 0., 4.) << std::endl;
  return 0;
  
}