#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

int main(){

  int rows=0;
  int columns=0;
  int non_zeros=0;

  ifstream mm_file;
  mm_file.open("/mnt/home/rysewykd/SummerOfCpp/Week1/matrixmarket.txt");
  
  if(!mm_file){
    cout << "Cannot open file";
  }

  string line;
  while(getline(mm_file,line)){
    if(line.at(0) != '%'){
      stringstream(line) >> rows >> columns >> non_zeros;
      break;
    }
  }

  cout << "Number of rows = " << rows << endl;
  cout << "Number of columns = " << columns << endl;
  cout << "Number of Non-Zeros = " << non_zeros << endl;

  mm_file.close();

}
