#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

static auto phone_book = std::map<std::string, unsigned long>({{"Frederik", 0001u}, {"Mark", 0002u}, {"Natasha", 0003u}, {"Mia", 0004u}});

bool name_exists(std::string name){
  return phone_book.find(name) != phone_book.end();
}

bool number_exists(unsigned long phone){
  for(auto a: phone_book){
    if (a.second == phone){
      return true;
    }
  }
  return false;
}

int main() {
  for(auto &a: {"Frederik", "Heinz"}){
    if (name_exists(a)){
      std::cout << a << " does exist!" << std::endl;
    }else{
      std::cout << a << " does NOT exist!" << std::endl;
    }
  }
  for(auto &a: {1u, 23u}){
    if (number_exists(a)){
      std::cout << a << " does exist!" << std::endl;
    }else{
      std::cout << a << " does NOT exist!" << std::endl;
    }
  }
   return 0;
}