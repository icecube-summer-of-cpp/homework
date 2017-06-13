#include "quiz1.h"

inline void enable_stream_exception(std::ios& io){
  io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

int main(int argc, char* argv[]) {
  if (argc<2){
    std::cout << "No file to read given" << std::endl;
    return NO_INPUT_FILE;
  }
  std::ifstream matrix_file;
  enable_stream_exception(matrix_file);
  try {
    matrix_file.open(argv[1]);
  }catch (...){
    std::cout << "Could not open file: " << argv[1] << std::endl;
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
  return SUCCESS;
}