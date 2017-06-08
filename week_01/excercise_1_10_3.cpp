/**
 * Summer of C++ - 2017
 * excercise_1_10_3.cpp
 * Purpose: reads the header of a
 *          matrix market file
 *
 * @author Mirco Huennefeld
 * @version 1.0 06/07/17
 */


// include necessary libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// empty error classes
class InputFileError{};
class HeaderError{};

/**
 * @brief get header information
 * @details Reads line after line to retrieve the header information
 *          Does not perform any checks, assumes correct data format.
 * 
 * 
 * @param input_file [description]
 * @param num_rows variable in which the number of rows is saved 
 * @param num_cols variable in which the number of columns is saved
 * @param num_non_zeros variable in which the number of non-zeros is saved
 */
void read_header(std::ifstream& input_file, 
                        uint& num_rows, 
                        uint& num_cols, 
                        uint& num_non_zeros)
{

    if( !input_file.good() ){
        throw InputFileError();
    }

    bool found_header_line = false;
    std::string header_line;

    // Read lines until the first non-empty line without an %
    // as the first character is found.
    // This is the header line
    while(!input_file.eof() && !found_header_line){
        std::getline(input_file, header_line);
        if(header_line[0] != '%' && header_line[0] != '\n' && header_line.length() > 0){
            found_header_line = true;
            std::cout << "Found the following header line:\n"
                      << header_line << std::endl << std::endl;
        }
    }
    
    // check if header line was found
    if (!found_header_line){

        // no header line was found
        throw HeaderError();
    }

    // header line was found and needs to be parsed
    // Simple parsing, assuming correct data format
    std::istringstream(header_line) >> num_rows >> num_cols >> num_non_zeros;
}




int main()
{   
    // define variables
    uint num_rows = 0;
    uint num_cols = 0;
    uint num_non_zeros = 0;

    // define input file
    std::string file = "MatrixMarketFile.txt";


    // open file
    std::cout << "Now opening " << file << std::endl;
    std::ifstream input_file(file);

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
        std::cerr << "Could not open file " << input_file << std::endl;
    }
    catch(HeaderError& e){
        std::cerr << "No header line was found in file." << std::endl;;

    }

    return 0;
}