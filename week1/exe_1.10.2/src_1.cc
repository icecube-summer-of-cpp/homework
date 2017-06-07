#include <iostream>
#include <string>

// Write the following declarations: pointer to a character, array of 10 integers, 
// pointer to an array of 10 integers, pointer to an array of character strings, pointer to pointer to a character, 
// integer constant, pointer to an integer constant, constant pointer to an integer. Initialize all these objects.

using namespace std;
int main(void)
{
	// Decalare and initialize to 0 or NULL
	char * ptr_char = NULL;
	int arr_int[10];
	int * ptr_int[10];
	for(int i = 0; i < 10; i++)
	{
		arr_int[i] = 0;
		ptr_int[i] = NULL;
	}
	string ptr_char_string = "";
	char ** ptr_ptr_char = NULL;
	const int const_int = (int)NULL;
	int * const ptr_const_int = NULL;
	const int * const const_ptr_const_int = NULL; 
}