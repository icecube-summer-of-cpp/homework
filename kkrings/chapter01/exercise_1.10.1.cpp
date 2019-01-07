/**
 * Solution to exercise 1.10.1
 */
#include <fstream>
#include <iostream>

int main()
{
    unsigned int age = 0;

    std::cout << "What is your age?" << std::endl;
    std::cin >> age;
    std::cout << "You are " << age << " years old." << std::endl;

    std::ofstream outfile("answer.txt");
    if (outfile.good())
    {
        outfile << "You are " << age << " years old." << std::endl;
    }
    else
    {
        std::cerr << "Could not write answer.txt." << std::endl;
    }
}
