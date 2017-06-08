/** 
 *  Summer of C++
 *  Week 1, Exercise 1.10.3
 *  @author: Federica Bradascio
 *
 * Read the header of a  Matrix Market file and print
 * the number of rows, the number of columns and the
 * number of non-zero elements on the spare matrix.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main ()
{
  string line;
  ifstream inputfile ("MatrixMarket.txt");
  int row, col, num_non_zero;
  if (inputfile.is_open())
  {
    while (getline(inputfile,line))
    {
      if (line[0]!='%'){
	cout << line << '\n';
	stringstream linestring(line);
	linestring >> row >> col >> num_non_zero;
	break;
      }
    }
    inputfile.close();
  }
  else cout << "Unable to open file"; 

  cout << "Rows = " << row << ", Columns = " << col
       << ", Number of non-zeroes = " << num_non_zero
       << endl;
  return 0;
}
