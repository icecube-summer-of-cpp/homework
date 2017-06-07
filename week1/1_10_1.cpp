/* Discovering Modern C++ (P. Gottschling)

    Exercise 1.10.1
    ===============
    Write a program that asks input from the keyboard
    and prints the result on the screen and
    writes it to a file. The question is:
    “What is your age?” */
#include <fstream>
#include <iostream>
#include <limits>

int main() {
    int age = 0;
    bool valid_input = false;

    while (!valid_input) {
        std::cout << "What is your age?" << std::endl;
        std::cin >> age;
        valid_input = std::cin;  // For valid (int) input std::cin will be true
        if (!valid_input) {
            // clearing the errorflag to give
            // cin the chance to be evaluated as true
            std::cin.clear();
            std::cout << "Fake news: Again please!" << std::endl;
            // clears the buffer in the stream. 'ignore' needs a length.
            // To clear everything the max stream length is retrieved from std
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << "Age entered: " << age << std::endl;

    std::ofstream outfile;
    outfile.open("1_10_1_file.txt", std::ofstream::out | std::ofstream::app);
    if (outfile.is_open()) {
        outfile << age << std::endl;
        outfile.close();
    } else {
        std::cout << "Error opening file; Age not appended to the File!";
    }
    return 0;
}
