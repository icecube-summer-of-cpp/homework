/*
 * 1. Write the following declarations:
 *      pointer to a character
 *      array of 10 integers
 *      pointer to an array of 10 integers
 *      pointer to an array of character strings
 *      pointer to pointer to a character
 *      interger constant
 *      pointer to an integer constant
 *      constant pointer to an integer
 *    Initialize all these objects.
 */



#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

int main(){

	char* c1= new char('a');
	cout << c1 << endl;
	int i1[]= {1,2,3,4,5,6,7,8,9,0};
	cout << i1 << endl;
	boost::shared_ptr<char> sc1(new char('b'));
	cout << sc1 << endl;	
	delete c1;

	return 0;
}
