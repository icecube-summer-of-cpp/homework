#include <vector>
#include <iostream>
#include <algorithm>

int main(){
  std::vector<double> v = {-9.3,-7.4,-3.8,-0.4,1.3,3.9,5.4,8.2}, v1,v2;
  v1 = v;
  v2 = v;
  std::cout << "Original: " ; 
  for (auto a: v){
    std::cout << a << " " ;
  }
  std::cout << std::endl;

  std::sort(begin(v1),end(v1),[](double i, double j){return abs(i) < abs(j);});
  
  std::cout << "Lambda: " ;
  for (auto a: v1){
    std::cout << a << " " ;
  }
  std::cout << std::endl;

  struct sort_f{
    auto operator() (double i, double j) const
    {
      return abs(i) < abs(j);
    }
  };

  std::sort(begin(v2),end(v2),sort_f());

  std::cout << "Functor: " ;
  for (auto a: v2){
    std::cout << a << " " ;
  }
  std::cout << std::endl;

  return 0;
}
