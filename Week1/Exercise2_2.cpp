#include<iostream>

int main(){
	int array[10];
	int newsize;
	std::cout << "Size for array: ";
	std::cin >> newsize;
	int * parray=new int[newsize];

	//delete[] parray;

	return 0;
}
