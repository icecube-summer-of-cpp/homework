// Summer of C++ 
// Homework Week 1 
// Excercise 1.10.3 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

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

#include "exercise_1_10_3.hpp"

inline void enable_stream_exception(std::ios& io){
    io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

int main(int argc, char* argv[]){
    
    int rows, cols, nonzeros;
    std::ifstream myFile;
        
    enable_stream_exception(myFile);
    try{
        if (argc!=2){ throw wrong_number_of_parameters{}; }
        auto fileName = argv[1];
        myFile.open(fileName);
    }catch(wrong_number_of_parameters& e1){
        std::cout << "wrong number of parameters" << std::endl;
        return 0;
    }catch(...){
        std::cout << "Could not open File" << std::endl;
        return 0;
    }
        
    std::string line;  
    try{
        while(!myFile.eof()){
                std::getline(myFile, line);
                // std::cout << line << std::endl;
                if (line.at(0) != '%'){break;}
        }
        myFile.close();
    }catch(...){
        std::cout << "Could not read from file" << std::endl;
        return 0;
    }
    
    try{
            std::istringstream(line) >> rows >> cols >> nonzeros;
    }catch(...){
        std::cout << "Could not find row, column and non zeros" << std::endl;
        return 0;
    }
            
    try{
        // check that we got the right numbers by printing them
        std::cout << "Rows: "<< rows << std::endl;
        std::cout << "Cols: "<< cols << std::endl;
        std::cout << "Non-Zeros: "<< nonzeros << std::endl;
    }catch(...){
        std::cout << "Nice we can not print to screen but try it any way for this error message!" << std::endl;
        return 0;
    }
    
    return 0;
}
