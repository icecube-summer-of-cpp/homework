/**
 * Summer of C++ - 2017
 * excercise_1_10_1.cpp
 * Purpose: Asks for the age of the user
 *             and saves this to a file
 *
 * @author Mirco Huennefeld
 * @version 1.0 06/07/17
 */


// include necessary libraries
#include <iostream>
#include <string>
#include <fstream>



/**
 * @brief Empty error class
 */
class InputError{};



/**
 * @brief Get age from user
 * @details This function will query the user
 *          to input an unsigned int. If the input 
 *          is not an unsigned integer, the user will
 *          be queried again. 
 *          
 * @param question A string containing the question.
 * 
 * @return age unsigned int
 */
unsigned int get_uint(std::string& question){

    // define variables
    bool got_valid_input = false;
    unsigned int answer = 0;

    // loop until we got a valid input 
    while(!got_valid_input){

        try{
            // print question
            std::cout << question << std::endl;

            // get input
            std::cin >> answer;

            // check if an error occured
            if (std::cin.fail() or std::cin.get() != '\n') {
                throw InputError();
            }

            // we now have a valid input
            got_valid_input = true;
        }

        catch(InputError& e){
            
            std::cout << "The value entered is not an unsigned int.\n"
                      << "Please try again."<<std::endl;

            // Clear error flag
            std::cin.clear();

            // Clear input buffer
            std::cin.ignore(10000,'\n');

        }
        catch(...){
            std::cout << "Something went wrong.." << std::endl;
        }
    }

    return answer;
}




int main()
{
    std::string question = "What is your age?";
    unsigned int age = get_uint(question);

    std::cout << "The age entered is: " << age << std::endl;

    // define output file
    std::string file = "age.txt";

    std::cout << "Now saving to " << file << std::endl;

    // open file
    std::ofstream output_file(file);

    // check if all is good and the file is opened
    if( output_file.good() ){
        output_file << "Age: "<< age << std::endl;
    }
    else{
        std::cerr << "Could not open file " << output_file << std::endl;
    }

    return 0;
}