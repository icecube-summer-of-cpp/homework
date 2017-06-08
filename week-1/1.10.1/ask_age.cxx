#include <iostream>

int main ()
{
    int age;
    std::cout << "What is your age?" << std::endl;
    std::cin >> age;
    
    if (age < 0)
    {
        std::cout << "I don't believe you!" << std::endl;
    }
    else
    {
        std::cout << "You are " << age << " years old." <<    std::endl;
    }
    
    return 0;
}
