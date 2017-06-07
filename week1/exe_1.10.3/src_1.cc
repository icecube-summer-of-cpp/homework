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

int main(void)
{
	char check_line;
	int rows_matrix = 0, columns_matrix = 0, num_non_zero_matrix = 0;
	string line;
	ifstream in_matrix_file;
	in_matrix_file.open("example_matrix_market");

	while(getline(in_matrix_file, line))
	{
		if(line.at(0) != '%')
		{
			stringstream linestream(line);
			linestream >> rows_matrix;
			linestream >> columns_matrix;
			linestream >> num_non_zero_matrix;
			break;
		}
	}
	cout << "Number of row : " << rows_matrix << "\tNumber of column : " << columns_matrix << 
		"\tNumber of non zero : " << num_non_zero_matrix << endl;
	return 0;
}