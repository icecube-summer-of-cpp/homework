/**
 * Solution to exercise 1.10.3
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    unsigned int nrow = 0, ncol = 0, nonzero = 0;

    std::ifstream infile("matrix.dat");
    if (infile.good())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            if (line[0] != '%')
            {
                std::istringstream stream(line);
                stream >> nrow >> ncol >> nonzero;
                break;
            }
        }
    }
    else
    {
        std::cerr << "Could not open matrix.dat." << std::endl;
    }

    std::cout << "Number of rows: " << nrow << ", "
              << "number of columns: " << ncol << ", "
              << "number of non-zero entries: " << nonzero
              << std::endl;
}
