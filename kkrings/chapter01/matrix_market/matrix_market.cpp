/**
 * Solution to first week's quiz
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix_market.hpp"

std::vector<unsigned int> read_matrix_market(const std::string& filename)
{
    // if something goes wrong with I/O return a vector of zeros
    std::vector<unsigned int> dimensions = {0, 0, 0};

    std::ifstream infile(filename);
    if (infile.good())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            if (line[0] != '%')
            {
                std::istringstream stream(line);
                stream >> dimensions[0] >> dimensions[1] >> dimensions[2];
                break;
            }
        }
    }
    else
    {
        std::cerr << "Could not open " << filename << ". "
                  << "Return zeros." << std::endl;
    }

    return dimensions;
}
