#include "quiz.hpp"
// matrix file: comments start with %
// first row:
// n_rows           n_cols          n_nonzero
// row number       col number      value real       (value imaginary)
// ...
/*
TASK:
-> DONE -> Read in the file, print n_rows, n_cols, n_nonzero.
-> DONE -> Create an executable which takes the filename as a parameter.
-> DONE -> The project needs to build with cmake.
-> DONE -> Split the code between a header file and source.
-> DONE -> The header should have protections against multiple inclusions.
Make sure all failures modes are handled sanely. 
*/
void print_matrix_header(std::ifstream& file)
{
    int rows, cols, nonzeros;
    std::string line;
    do
    {
        std::getline(file, line);
    }while(line[0]=='%');
    
    std::stringstream linestream;
    linestream << line;
    linestream >> std::skipws >> rows >> cols >> nonzeros;
    std::cout << rows << " " << cols << " " << nonzeros << std::endl;
}

int main(int argc, char* argv[])
{
    do
    std::cout << "Reading file " << argv[1] << std::endl;
    std::ifstream matrix_file(argv[1]);
    print_matrix_header(matrix_file);
    return 0;
}