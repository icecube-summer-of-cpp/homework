/**
 * Summer of C++ - 2017
 * Quiz 1 - main program
 * Purpose: reads the header of a
 *          matrix market file
 *
 * @author Mirco Huennefeld
 * @version 1.0 06/08/17
 */


// include necessary libraries
#include <iostream>
#include <string>
#include <fstream>
#include "matrix_reader.h"


void print_usage(char* argv[]){
    // Tell the user how to run the program
    std::cerr << "\nUsage: " << argv[0] << " Path/to/Matrix/Market/file\n";
    std::cerr << "\n  The filename of the Matrix Market File needs to be passed.\n";
}


int main(int argc, char* argv[])
{   
    // define variables
    unsigned int num_rows = 0;
    unsigned int num_cols = 0;
    unsigned int num_non_zeros = 0;

    // Check the number of parameters
    if (argc != 2) {
        print_usage(argv);
        return 1;
    }

    //std::string file = "MatrixMarketFile.txt";
    std::string file = argv[1];


    // open file
    std::cout << "Now opening " << file << std::endl;
    std::ifstream input_file(file.c_str());

    try{

        // get information from header
        read_header(input_file, num_rows, num_cols, num_non_zeros);

        // print header information:
        std::cout << "Header Information:\n";
        std::cout << "\tNumber of rows: " << num_rows << std::endl;
        std::cout << "\tNumber of columns: " << num_cols << std::endl;
        std::cout << "\tNumber of non zeros: " << num_non_zeros << std::endl;
    }
    catch(InputFileError& e){
        std::cerr << "Could not open file " << file << std::endl;
    }
    catch(HeaderError& e){
        std::cerr << "No header line was found in file." << std::endl;;

    }

    return 0;
}