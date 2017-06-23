#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class test{
std::vector<double> tmp;
public:
test(std::vector<double> tmp): tmp(tmp){};
};

int main(int argc, char const *argv[])
{
  auto a = test({1,2,3,4,5,6,7,8});
  a = test({});
  return 0;
}