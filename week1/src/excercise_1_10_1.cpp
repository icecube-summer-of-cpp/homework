/*
 * Write a program that asks input from the keyboard and prints the 
 * result on the screen and writes it to a file. 
 * The question is: "What is your age?"
 */

#include <iostream>
#include <limits>
#include <fstream>

int main(){
    

    // Read in age
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

    // we may check if a print out was successful

    // print in file
    std::ofstream myfile("age.txt");
    // we should check if file exists
    // we should check if file open was successful
    myfile << age << std::endl;
    // we should check writing to file was successful
    myfile.close();
    // we should check that file is okay
    
    return 0;
}
