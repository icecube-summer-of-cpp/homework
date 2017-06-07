#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
  //PART 1

  //pointer to a character
  char* character = new char;
  *character = 'o';
  delete character;

  //array of 10 integers
  int integers[10];
  for(int i=0;i<10;i++){integers[i]=i;}
  
  //pointer to array of 10 integers
  int  *ptrarray = new int[10];
  for(int i=1; i<11;i++){ptrarray[i-1]=i;}
  delete[] ptrarray;

  //pointer to an array of character strings
  char* nums = new char[4];
  for(int i=0;i<3;i++){nums[i]='u';};
  delete[] nums;

  //pointer to pointer to a character
  char* char1 = new char;
  *char1 = 'm';
  char** char2 = &char1;
  delete char1;
  delete char2;

  //integer constant
  const int i = 3;

  //pointer to an integer constant
  int j = 4;
  const int* ptr_j = &j;
  delete ptr_j;

  //constant pointer to an integer
  int number = 5;
  int *const ptr_number = &number;
  delete ptr_number;


  // PART 2

  // array on the stack
  double stack_array[5];


  // array on the heap
  double* heap_array = new double[5];
  delete[] heap_array;

}
