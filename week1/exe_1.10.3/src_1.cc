// The Matrix Market data format is used to store dense and sparse matrices in ASCII format. 
// The header contains some information about the type and the size of the matrix. 
// For a sparse matrix, the data is stored in three columns. The first column is the row number, 
// the second column the column number, and the third column the numerical value. When the value type of the matrix is complex, 
// a fourth column is added for the imaginary part.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void read_matrix_file(const char * fname) noexcept;

struct cannot_open_file{};

int main(void)
{
	char check_line;
	int rows_matrix = 0, columns_matrix = 0, num_non_zero_matrix = 0;
	string line;
	
	try{
		read_matrix_file("market");
	}catch(cannot_open_file & e){
		cout << "Cannot open the file" << endl;
	}
	// ifstream in_file("example_matrix_market");
	// in_file.open("example_matrix_market");

	// while(getline(in_file, line))
	// {
	// 	if(line.at(0) != '%')
	// 	{
	// 		stringstream linestream(line);
	// 		linestream >> rows_matrix;
	// 		linestream >> columns_matrix;
	// 		linestream >> num_non_zero_matrix;
	// 		break;
	// 	}
	// }
	// cout << "Number of row : " << rows_matrix << "\tNumber of column : " << columns_matrix << 
	// 	"\tNumber of non zero : " << num_non_zero_matrix << endl;
	return 0;
}

void read_matrix_file(const char * fname) noexcept
{
	fstream in_file(fname);
	cout << in_file.is_open() << endl;

	if(!in_file.is_open())
		throw cannot_open_file{};
}