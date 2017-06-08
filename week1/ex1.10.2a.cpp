/**
 *  Summer of C++
 *  Week1, Exercise 1.10.2 - part (1)
 *  @author: Federica Bradascio
 *
 *  Write and initialize the following declarations: pointer to 
 *  a character, array of 10 integers, pointer to an array of 10 
 *  integers, pointer to an array of character strings, pointer 
 *  to pointer to a character, integer constant, pointer to an 
 *  integer constant, constant pointer to an integer.
 */

#include <iostream>
#include <fstream>
using namespace std;

int main()
{ 
  // pointer to a character
  char val = 'c';
  char* ptr_char = &val;
  
  // array of 10 integers
  int arr[10] = {0};

  // pointer to an array of 10 integers
  int* ptr_intarr = new int[10];
  for(int i=0; i<10; ++i)
      ptr_intarr[i] = 0;
  
  // pointer to an array of character strings
  char chararr[5] = {'a', 'b', 'c', 'd', 'e'};
  char* ptr_chararr = chararr;
  
  // pointer to pointer to a character
  char** ptr_ptr_char = new char*;
  ptr_ptr_char = &ptr_chararr;
  
  //integer constant
  const int const_int = 0;

  //pointer to an integer constant
  const int* ptr_constint = &const_int;

  //constant pointer to an integer
  int x = 0;
  int * const ptr_intconst = &x;

  return 0;
 }
