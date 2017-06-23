#include <string>
#include <sstream>
#include <iostream>

template <typename T>
std::string to_string(T x){
  std::string res;
  std::stringstream tmp;
  tmp << x;
  tmp >> res;
  return res;
}


int main(){
  int a {5};
  std::cout << to_string(a) << std::endl;
  return 0;
}