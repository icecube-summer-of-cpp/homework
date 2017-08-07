/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 1.10.1
 * Write a program that asks input from the keyboard and prints the result on
 * the screen and writes it to a file. The question is: “What is your age?”
 */

#include <iostream>
#include <fstream>

int main()
{
    // First attempt at getting age
    std::cout << "What is your age? ";
    int age;
    std::cin >> age;

    // Loop until a reasonable age is entered
    while (age<=0 || age>125) {
        // Catches non-integer inputs
        if (std::cin.fail()) {
            std::cout << "Sorry, I only understand ages in numbers. " <<
            "Please try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
        // Handles unrealistic ages
        else {
            std::cout << "You are " << age << "? That doesn't seem right..."
            << std::endl;
        }
        
        std::cout << "What is your age? ";
        std::cin >> age;
    }

    // Write age to screen
    std::cout << "Okay, so you are " << age << " years old." << std::endl;
    
    // Write age to file
    std::ofstream agefile("age.txt");
    agefile << age << std::endl;
    std::cout << "I have recorded your age in the file age.txt" << std::endl;

}