#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <complex>

#define matrix_file_name "../MatrixMarket.csv"

inline void enable_stream_exception(std::ios& io){
  io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

enum return_vals{
    SUCCESS,
    COULD_NOT_OPEN_FILE,
    COULD_NOT_READ_FILE,
};

int main() {
  std::ifstream matrix_file;
  enable_stream_exception(matrix_file);
  try {
    matrix_file.open(matrix_file_name);
  }catch (...){
    std::cout << "Could not open file." << std::endl;
    return COULD_NOT_OPEN_FILE;
  }
  try {
    std::string tmp;
    while (std::getline(matrix_file, tmp)) {
      if (tmp[0] == '%') {
        continue;
      }
      break;
    }
    int row, col, nonzero;
    std::stringstream(tmp) >> row >> col >> nonzero;
    std::cout << "Rows: " << row << " Cols: " << col << " Nonzero: " << nonzero << std::endl;
  }catch (...){
    std::cout << "Either could not read from file or could not find the header line" << std::endl;
    return COULD_NOT_READ_FILE;
  }
  
  //first try to reconstruct the matrix but as we do no thave a good matrix type yet, i will stop here
  
  //auto matrix = std::make_unique<std::vector< std::vector<double> >>();
  //(*matrix).reserve(row);
  //for(auto i : *matrix){
  //  i.reserve(col);
  //}
  //int row_i, col_i;
  //double real;
  //try{
  //  while (std::getline(matrix_file, tmp)) {
  //    if (tmp[0] == '%') {
  //      continue;
  //    }
  //    std::stringstream(tmp) >> row_i >> col_i >> real;
  //    std::cout << row_i << col_i << real << std::endl;
  //    (*matrix)[row_i][col_i] = real;
  //  }
  //}catch (...){//eof}
  return SUCCESS;
}