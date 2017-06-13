/* Ben Hokanson-Fasig
 * Summer of C++ - Quiz 1
 */

#include <iostream>
#include <fstream>
#include <sstream>

struct MatrixInfo {
    double rows = -1;
    double columns = -1;
    double entries = -1;
};

MatrixInfo get_info(char*);

void print_info(MatrixInfo);