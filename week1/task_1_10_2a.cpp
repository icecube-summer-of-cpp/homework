#include <iostream>
#include <memory>
using namespace std;


int main(){

	char* c1= new char('a');
	cout << &c1 << " " << c1 << endl;

	int i1[]= {1,2,3,4,5,6,7,8,9,0};
	cout << i1 << " " << *i1 << endl;

	return 0;
}
