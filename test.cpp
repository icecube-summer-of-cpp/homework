#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char const *argv[])
{
  std::ifstream infile("../MM2.csv");
  
  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream instream(line);
    if (line[0] == '%') {
      continue;
    }
    else {
      int rows, cols, nonzeros;
      instream >> rows >> cols >> nonzeros;
      std::cout << "Rows     = " << rows << std::endl
                << "Cols     = " << cols << std::endl
                << "nonzeros = " << nonzeros << std::endl;
      break;
    } // Close after first valid row
  }
  infile.close();
  return 0;
}