/** 
 *  Summer of C++
 *  Week 1, Exercise 1.10.2 - part (2)
 *  @author: Federica Bradascio
 *  
 *  Make a small program that creates arrays on the stack (fixed-size 
 *  arrays) and arrays on the heap (using allocation). Use valgrind 
 *  to check what happens when you do not delete them correctly.
 */

#include <iostream>
#include <memory>
using namespace std;

int main()
{
  int stack_array[100];
  int *heap_array = new int[100];
  delete[] heap_array;

  // valgrind --leak-check=full --show-leak-kinds=all ex1.10.2b
  
  return 0;
 }
