#include "solution.h"

using namespace std;

void with_io_exceptions(ios& io){
	io.exceptions(ios_base::badbit | ios_base::failbit);
}

int main(int argc,char* argv[]){
	assert (argc==2 && "You need to add one (and only one) parameter");	
	ifstream matrix_market_file;
	with_io_exceptions(matrix_market_file);
	try{
		matrix_market_file.open(argv[1]);
	}
	catch(...){
		cout << "Couldn't open "<< argv[1] << ", captain!" << endl;
		exit(EXIT_FAILURE);
	}

	string str;
	try{

		while (getline(matrix_market_file,str)){
			if (str[0] == '%') continue;
			break;
		}
	}
	catch(...){
		cout << "Something went wrong when reading the file, captain" <<endl;
		exit(EXIT_FAILURE);
	}
	int rows,columns,nonzeroes;
	stringstream(str) >> rows >> columns >> nonzeroes;
	cout << "Number of rows: " << rows << "\n"
	<< "Number of columns: " << columns << "\n"
	<< "Number of non zeroes: " << nonzeroes << "\n";


	matrix_market_file.close();
	
	return 0;
}
