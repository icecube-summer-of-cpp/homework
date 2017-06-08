#include <iostream>
#include <fstream>  // Both read and write from/to files
#include <string>
using namespace std;

int main ()
{
  string line;
  ifstream inputfile ("MatrixMarket.txt");
  if (inputfile.is_open())
    {
      while (getline(inputfile,line))
	{if (line[0]!='%')  // only care about the first line not starting with %
	    {cout << line << '\n';
	    break;}
	}
      inputfile.close();
    }
  else cout << "Unable to open file"; 

  return 0;
}
