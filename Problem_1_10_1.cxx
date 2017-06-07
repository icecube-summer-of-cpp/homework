#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
  ofstream myfile;
  myfile.open("/mnt/home/rysewykd/SummerOfCpp/Week1/Problem_1_10_1.txt");

  int age_input;

  cout << "What is your age? ";
  cin >> age_input;
  cout << "You are " << age_input << " years old." << endl;


  myfile << "What is your age?" << endl;
  myfile << age_input << endl;
  myfile << "You are " << age_input << " years old." << endl;
}
