#include <iostream>
#include <fstream>


int main ()
{
    int age;
    std::cout << "What is your age?" << std::endl;
    std::cin >> age;
    
    std::ofstream age_file("age.txt");
    
    if (age < 0)
    {
        std::cout << "I don't believe you!" << std::endl;
        age_file << age << std::endl;
    }
    else
    {
        std::cout << "You are " << age << " years old." <<    std::endl;
        age_file << age << std::endl;
    }
    
    return 0;
}
