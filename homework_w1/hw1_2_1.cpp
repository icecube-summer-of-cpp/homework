#include <iostream>
#include <string>
using namespace std;

int main ()
{
  char x1='a';
  char* x=&x1;  // pointer to character
  int y[10]={0}; // array of 10 integers
  int* z = y; // pointer to above array
  char ch[2] = {'b','c'};
  char* a = ch; // pointer to array of characters
  //char* b=x; copy of pointer x
  char** b = &x; // pointer to pointer to character
  int const c=0; //integer constant
  int const* d = &c; //pointer to const int
  int * const e =&y[0]; // constant pointer to integer (here same as pointer to array?)
  
  return 0;
}

