// Summer of C++ 
// Homework Week 1 
// Excercise 1.10.1 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

/*
 * Write a program that asks input from the keyboard and prints the 
 * result on the screen and writes it to a file. 
 * The question is: "What is your age?"
 */

#include <iostream>
#include <limits>
#include <fstream>

int main(){
    
    // declareation of variables
    int age = -1;
    bool age_acceptable = false;

    // ask for input until we get a valid input.
    while(!age_acceptable){
        std::cout << "What is your age?" << std::endl;
        std::cin >> age;

        // check if input matches type of age and range of age
        age_acceptable = std::cin;
        age_acceptable = age_acceptable && (age>=0);
        
        if(!age_acceptable){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; please re-enter." << std::endl;
        }
    } // while !age_acceptable
    
    // print to screen
    std::cout << "Your are " << age << " years old."<< std::endl;

    // print in file
    std::ofstream myfile("age.txt");
    if(myfile.is_open()){
        myfile << age << std::endl;
        myfile.close();
    }
    
    return 0;
}
