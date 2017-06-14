#include <iostream>
#include <fstream>

using namespace std;

int main(){
	cout << "How many years have thou walked the Earth?" << endl;
	int age;
	cin >> age;
	cout << age << " years and still you accomplished nothing!" << endl;

	ofstream age_file;
	
	age_file.open("age.txt");
	age_file << age << endl;
	age_file.close();
		
	return 0;
}
