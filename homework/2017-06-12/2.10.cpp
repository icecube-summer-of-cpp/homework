//
// Created by Frederik Lauber on 12.06.17.
//
#include "polynom.h"
//not using a extra copy assignment or non default destructor

int main(){
  Polynom a({1,1});
  Polynom b({-1,1});
  std::cout << "1)\t"<< a << std::endl;
  std::cout << "2)\t"<< b << std::endl;
  std::cout << "1+2)\t"<< a+b << std::endl;
  std::cout << "1*2)\t"<< a*b << std::endl;
  std::cout << "Eval 1@val(7)\t" << eval(a, 7) << std::endl;
  std::cout << "Nested 1 in 2\t" << eval(b, a) << std::endl;
  return 0;
}