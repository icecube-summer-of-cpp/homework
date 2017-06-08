#include <iostream>
#include <fstream>  // Both read and write from/to files
#include <string>
using namespace std;

int main ()
{
  string age; // since this is only used to write into a file, want to accept numerical and text input
  cout << "What is your age in years?" << "\n";
  cin >> age;
  cout << "You claim to be " << age << " years old. \n";
  ofstream outfile; 
  outfile.open("Age.txt");
  outfile << age << endl;
  outfile.close();

  return 0;
}

