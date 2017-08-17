/**
 * Solution to first week's quiz
 */
#ifndef MATRIX_MARKET_MATRIX_MARKET_HPP
#define MATRIX_MARKET_MATRIX_MARKET_HPP

#include <string>
#include <vector>

/**
 * Read the dimensions of the Matrix Market data file given by filename.
 */
std::vector<unsigned int> read_matrix_market(const std::string& filename);

#endif
