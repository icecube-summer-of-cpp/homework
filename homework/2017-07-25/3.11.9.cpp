#include <iostream>

template <class T, unsigned int N>
unsigned int array_size(T (&tmp)[N]){
  return N;
};


int main(){
  int c[100];
  std::cout << array_size(c) << std::endl;
  return 0;
}