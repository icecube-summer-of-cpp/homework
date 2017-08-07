/* Ben Hokanson-Fasig
 * Summer of C++ - Quiz 1
 */

#include "mreader.hpp"

MatrixInfo get_info(char* filename)
{
    std::ifstream filestream;
    // Deal with I/O issues via exception
    filestream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    // Open file
    try {
        filestream.open(filename);
    }
    catch (...) {
        std::cout << "File not found" << std::endl;
        exit(1);
    }

    MatrixInfo info;

    // Read file line-by-line
    std::string line;
    while(!filestream.eof()) {
        std::getline(filestream,line);
        if (line.compare(0,1,"%",0,1)==0){
            continue;
        }
        else {
            // At first non-comment line, use stringstream to get data
            std::stringstream ss;
            ss << line;
            ss >> info.rows >> info.columns >> info.entries;
            break;
        }
    }

    return info;
}


void print_info(MatrixInfo info)
{
    std::cout << "Rows: " << info.rows << std::endl;
    std::cout << "Columns: " << info.columns << std::endl;
    std::cout << "Non-zero entries: " << info.entries << std::endl;
}


int main(int argc, char* argv[])
{
    // Make sure filename is provided by command line
    if (argc!=2) {
        std::cout << "Please provide a Matrix Market file" << std::endl;
        exit(1);
    }
    
    MatrixInfo info = get_info(argv[1]);
    
    if (info.rows<0 || info.columns<0 || info.entries<0) {
        std::cout << "Error reading file" << std::endl;
        exit(2);
    }

    print_info(info);
}