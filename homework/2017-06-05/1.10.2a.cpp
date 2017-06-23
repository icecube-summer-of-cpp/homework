#include <iostream>
#include <memory>
#include <vector>

//_g -> pref. method without memory leaks
//_b -> old way which needs delete to not lose memory
//included both as the exercise only said pointer or array and did not specify
//if unique_ptr and vectors where meant

int main() {
  auto p2char_g = std::make_unique<char>('a');
  //char *p2char_b = new char('a');
  
  std::vector<int> a10ints_g = {0,1,2,3,4,5,6,7,8,9};
  //int a10ints_b[10] = {0,1,2,3,4,5,6,7,8,9};
  
  auto pa10ints_g = std::make_unique<std::vector<int>>(std::vector<int> {0,1,2,3,4,5,6,7,8,9});
  //int *pa10ints_b = new int[10]{0,1,3,4,5,6,7,8,9};
  
  auto p2aofcharstrings_g = std::make_unique<std::vector<std::string>>(std::vector<std::string> {"Foo", "Bar"});
  //char** p2aofcharstrings_b = new char*[2]{"Foo", "Bar"};
  
  auto p2p2c_g = std::make_unique<std::unique_ptr<char>> (std::make_unique<char>('a'));
  //char **p2p2c_b = new char*{new char('a')};
  
  const int cint = 1;
  auto p2cint_g = std::make_unique<const int>(2);
  //const int * p2cint_b = new const int(2);
  
  const auto p2intc_g = std::make_unique<int>(3);
  //int * const p2intc_b = new int(3);
  
  std::cout << *p2char_g << std::endl;
  //std::cout << *p2char_b << std::endl;
  
  for(auto i : a10ints_g){
    std::cout << i << std::endl;
  }
  
  for(auto i : *pa10ints_g){
    std::cout << i << std::endl;
  }
  
  for(auto i : *p2aofcharstrings_g){
    std::cout << i << std::endl;
  }
  
  std::cout << **p2p2c_g << std::endl;
  std::cout << cint << std::endl;
  std::cout << *p2cint_g << std::endl;
  std::cout << *p2intc_g << std::endl;
  return 0;
}