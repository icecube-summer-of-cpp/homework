#include <iostream>
#include <fstream>

// Write a program that asks input from the keyboard and prints the result on the screen and writes it to a file. 
// The question is: “What is your age?”

using namespace std;

int main(void)
{
	int input_age; 

	cout << "What is your age? ";
	cin >> input_age;

	cout << "Age : " << input_age << endl;

	ofstream age_file;
	age_file.open("age.txt");
	age_file << "Your age is " << input_age << endl;
	age_file.close();
	return 0;
}