#include<iostream>
#include<sstream>
#include<string>


template <typename T>
std::string to_string(const T& a){
  std::stringstream ss;
  ss << a;
  return ss.str();
}

int main(){
  std::string test = to_string(1);
  std::cout << "The test is: " << test << std::endl;
  return 0;
}

