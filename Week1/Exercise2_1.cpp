#include <memory>

int main(){
	/*	PART I	    */

	//pointer to character
	char vc = 'c';
	char* pchar = &vc;
	
	//array of 10 integers
	int intarray[10];
	for (int i=0;i<10;i++){
		intarray[i] = i*2;
	}

	//pointer to an array of 10 integers
	//Ward: intarray points to first element of
	//the array. I.e. intarray == &intarray[0]
	int* pintarray=intarray;

	//pointer to an array of character strings
	char charstrings[] = {'s','t','r','i','n','g','s'};
	char* pcharstrings = charstrings;
	
	//pointer to pointer to a character
	char ch = 'c';
	char* pch = &ch;
	char** ppch = &pch;

	//integer constant
	const int i = 3;

	//pointer to integer constant
	const int * pi = &i;

	//constant pointer to an integer
	int vj = 4;
	int * const pvj = &vj;
	
	return 0;
}
