/**
 * Solution to first week's quiz
 */

#include <iostream>
#include "matrix_market.hpp"

int main()
{
    auto dimensions = read_matrix_market("matrix.dat");

    std::cout << "Number of rows: " << dimensions[0] << ", "
              << "number of columns: " << dimensions[1] << ", "
              << "number of non-zero entries: " << dimensions[2]
              << std::endl;
}
