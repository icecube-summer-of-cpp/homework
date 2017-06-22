#include <iostream>
#include <fstream>
using namespace std;

int main(){
	int age = 0;
	cout << "Hello you!" << endl;
	cout << "How old are you?" << endl;
	cin >> age;
	while (cin.fail()){
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Sorry, I did not understand ... How old are you? Please enter a valid number" << endl;
		cin >> age;
	}
	cout << "So you are " << age << " years old!" << endl;

	ofstream save_file("my_age.txt");
	save_file << age << endl;
	
	return 0;
}
