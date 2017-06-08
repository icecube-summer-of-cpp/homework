#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/*
// Doesn't work, can't get the row, col, nonzero numbers extracted
// using that sstream thing
*/

int main(int argc, char const *argv[])
{
    std::ifstream infile("market_matrix.dat");

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream instream(line);
        // std::cout << line << std::endl;

        if (line[0] == '%') {
            continue;
            // std::cout << "-> Comment line" << std::endl;
        }
        else {
            std::cout << line << std::endl;

            int rows, cols, sparse_nonzeros;
            instream >> rows >> cols >> sparse_nonzeros;
            std::cout << "Rows = " << rows
                      << " Cols = " << cols
                      << " nonzeros = " << sparse_nonzeros
                      << std::endl;
            break;
        } // Close after first valid row
    }

    return 0;
}