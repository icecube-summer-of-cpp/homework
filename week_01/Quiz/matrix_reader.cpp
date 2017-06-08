/**
 * Summer of C++ - 2017
 * Quiz 1 - implementation of matrix_reader
 * Purpose: reads the header of a
 *          matrix market file
 *
 * @author Mirco Huennefeld
 * @version 1.0 06/08/17
 */


// include necessary libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "matrix_reader.h"

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
                        unsigned int& num_rows, 
                        unsigned int& num_cols, 
                        unsigned int& num_non_zeros)
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
