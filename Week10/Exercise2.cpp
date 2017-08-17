#include <iostream>
#include <map>

std::string searchNumber(const std::map<std::string,unsigned long>& numbers)
{
  for (auto it = numbers.begin(); it != numbers.end(); ++it )
    if (it->second == 111)
        return it->first;
}

int main(){

  std::map<std::string,unsigned long> numbers = 
  {{"John Snow", 111}, {"Night King",222}, {"Denaerys",333},{"Cercei",444}};
  std::cout << "John Snow's number: " << numbers["John Snow"] << std::endl;
  std::cout << "Drogon's number: " << numbers["Drogon"] << std::endl;

  std::cout << "Name of number 111: " << searchNumber(numbers) << std::endl;

  return 0;
}
