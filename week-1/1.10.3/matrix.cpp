#include "matrix.hpp"
// matrix file: comments start with %
// first row:
// n_rows           n_cols          n_nonzero
// row number       col number      value real       (value imaginary)
// ...
// task: read in the file, print n_rows, n_cols, n_nonzero
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

int main()
{
    std::ifstream matrix_file("market_matrix.dat");
    print_matrix_header(matrix_file);
    return 0;
}