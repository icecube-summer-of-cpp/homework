/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 1.10.3
 * The Matrix Market data format is used to store dense and sparse matrices in
 * ASCII format. The header contains some information about the type and the
 * size of the matrix. For a sparse matrix, the data is stored in three columns.
 * The first column is the row number, the second column the column number, and
 * the third column the numerical value. When the value type of the matrix is
 * complex, a fourth column is added for the imaginary part.
 * The first line that does not start with % contains the number of rows, the
 * number of columns, and the number of non-zero elements on the sparse matrix.
 * Use fstream to read the header of a Matrix Market file and print the number
 * of rows and columns, and the number of non-zeroes on the screen.
 */

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
    // Make sure filename is provided by command line
    if (argc!=2) {
        std::cout << "Please provide a Matrix Market file" << std::endl;
        exit(1);
    }

    double rows, cols, entries;
    std::ifstream matrix;
    // Deal with I/O issues via exception
    matrix.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    // Open file
    matrix.open(argv[1]);

    // Read file line-by-line
    std::string line;
    while(!matrix.eof()) {
        std::getline(matrix,line);
        if (line.compare(0,1,"%",0,1)==0){
            continue;
        }
        else {
            // At first non-comment line, use stringstream to get data
            std::stringstream ss;
            ss << line;
            ss >> rows >> cols >> entries;
            break;
        }
    }

    std::cout << "Rows: " << rows << std::endl;
    std::cout << "Columns: " << cols << std::endl;
    std::cout << "Non-zero entries: " << entries << std::endl;
}