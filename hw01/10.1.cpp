#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
    float age;
    std::ofstream outfile("./age.txt");

    std::cout << "What is your age?" << std::endl;
    std::cin >> age;

    std::cout << "Your age is " << age << std::endl;
    outfile << "Your age is " << age << std::endl;

    return 0;
}
