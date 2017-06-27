#include <iostream>
#include <string>
#include <memory>
#include <typeinfo>
// Write the following declarations: pointer to a character, array of 10 integers, 
// pointer to an array of 10 integers, pointer to an array of character strings, pointer to pointer to a character, 
// integer constant, pointer to an integer constant, constant pointer to an integer. Initialize all these objects.

using namespace std;
int main(void)
{
	unique_ptr<char> ptr_ch{new char};

	ptr_ch = nullptr;

	unique_ptr<int[]> arr_int{new int[10]};

	unique_ptr<int * []> ptr_int2{new int * [10]};

	for(int i = 0; i < 10; i++)
	{
		arr_int[i] = 0;
		ptr_int2[i] = nullptr;
	}
	
	unique_ptr<string> ptr_str_arr{new string};
	
	unique_ptr<char * > ptr_ch_ptr{new char * };
	
	const int const_int = (int)NULL;

	auto ptr_const_int = make_unique<const int>(2);

	const auto const_ptr_int = make_unique<int>(1);

}