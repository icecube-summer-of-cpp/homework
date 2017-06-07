#include <iostream>

int main(void)
{
	int stack_arr[10]; // creates arrays on stack
	int * heap_arr; // creates arrays on heap

	heap_arr = new int[10];
	delete[] heap_arr;

}