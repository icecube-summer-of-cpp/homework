// The Matrix Market data format is used to store dense and sparse matrices in ASCII format. 
// The header contains some information about the type and the size of the matrix. 
// For a sparse matrix, the data is stored in three columns. The first column is the row number, 
// the second column the column number, and the third column the numerical value. When the value type of the matrix is complex, 
// a fourth column is added for the imaginary part.
#include <iostream>
 #include <fstream>
 #include <sstream>
 #include <memory>
 #include <vector>
 #include <complex>
using namespace std;

inline void enable_stream_exception(std::ios& io){
	io.exceptions(std::ios::badbit | std::ios::failbit);
}

enum process_situation{
	FAIL,
	SUCCESS,
};

int main(int argc, char* argv[])
{
	string file_name;
	int number;
	ifstream in_file;

	if(argc < 2)	{
		cout << "Please input file name : ";
		cin >> file_name;
	}
	else {
		file_name = argv[1];
	}

	fstream check_file(file_name.c_str());
	enable_stream_exception(in_file);
	try{
		in_file.open(file_name.c_str());
	} catch(std::ios_base::failure &fail){
		cout << "You wrote wrong file name" << endl;
		return FAIL;
	} 

	string line;
	int rows_matrix = 0, columns_matrix = 0, num_non_zero_matrix = 0;
	 
	while(getline(in_file, line))
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