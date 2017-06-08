/**
 * Summer of C++ - 2017
 * Quiz 1 - matrix_reader header
 * Purpose: reads the header of a
 *          matrix market file
 *
 * @author Mirco Huennefeld
 * @version 1.0 06/08/17
 */


// include guards
#ifndef MATRIX_READER_H_
#define MATRIX_READER_H_

// include necessary libraries
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
                        unsigned int& num_rows, 
                        unsigned int& num_cols, 
                        unsigned int& num_non_zeros);

#endif /* MATRIX_READER_H_ */