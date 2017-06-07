#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;


int main(){
    ifstream infile;
    infile.open("test_matrix.dat");
    if (infile.is_open()) {
        string str;
        while (getline(infile, str)){
            if (str[0] == '%') continue;
            break;
        }
        int rows, cols, not_zero;
        stringstream(str) >> rows >> cols >> not_zero;
        cout << "# rows: " << rows << "\n"
        << "# cols: " << cols << "\n"
        << "# not zero: " << not_zero << "\n";
        infile.close();
        return 0;
    } else {
        std::cout << "Error opening file; Age not appended to the File!";
        infile.close();
        return 1;
    }
}
