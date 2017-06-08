#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char const *argv[])
{
    std::ifstream infile("market_matrix.dat");

    std::string line;
    while (std::getline(infile, line))  // res line by line
    {
        std::istringstream instream(line);  // make stream from string
        if (line[0] == '%') {  // skip comments
            continue;
        }
        else {  // extract data from first valid line with 3 cols
            int rows, cols, nonzeros;
            std::cout << line << std::endl;
            instream >>  std::skipws >> rows >> cols >> nonzeros;
            std::cout << "Rows     = " << rows << std::endl
                      << "Cols     = " << cols << std::endl
                      << "nonzeros = " << nonzeros << std::endl;
            break;
        } // just close after first valid row
    }
    infile.close();
    return 0;
}