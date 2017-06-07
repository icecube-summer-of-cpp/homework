// Header file for 
// Summer of C++ 
// Homework Week 1 
// Excercise 1.10.3 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann, Lisa Schumacher, Joeran Stettner

/* The Matrix Market data format is used to store dense and sparse matrices in ASCII format.
 * The header contains some information about the type and the size of the matrix. For a sparse matrix, the data is stored in three columns. The fist column is the row number, the
 * second column the column number, and the third column the numerical value. When the value type of the matrix is complex, a fourth column is added for the imaginary part.
 *  An example of a Matri Market file is
 * 
 * %%MatrixMarket martix coordinate real general
 * %
 * % ATHENS course matrix
 * %
 *           2025           2025             100015
 *              1              1         .9273558001498543E-01
 *              1              2         .3545880644900583E-01
 * ....................
 * 
 * The first line that does not start with % contains the number of rows, the number of columns,
 * and the number of non-zero elements on the sparse matrix.
 * Use fstream to read the header of a Matrix Market file and print the number of rows and columns, and the number of non-zeroes on the screen.
 */

#ifndef EXERCISE_1_10_3
#define EXERCISE_1_10_3

#include <iostream>
#include <sstream>
#include <fstream>

struct wrong_number_of_parameters {};

#endif
