#include <vector>
#include <algorithm>
#include <iostream>

struct sort_mag{
    bool operator()(double x, double y){
      return x < y;
    }
};

int main()
{
  auto v = std::vector<double>({-9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2});
  std::sort(v.begin(), v.end(), [](double x, double y){return x<y;});
  std::sort(v.begin(), v.end(), sort_mag());
  for(auto & i : v){
    std::cout << i << std::endl;
  }
  return 0;
  
}