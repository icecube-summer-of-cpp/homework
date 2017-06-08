#include <iostream>
#include <fstream>  // Both read and write from/to files
#include <string>
using namespace std;

void create_y();
void create_z();

int main ()
{
  int x[10]={0}; //heap
  create_y(); // calls create_y to stack

  int w[10]={3}; //heap
  int v[10]={4}; //heap

  return 0;
}

void create_y()
{
  int y[10]={1}; //stack
  create_z(); // calls create_z to stack
}


void create_z()
{
  int z[10]={2}; //stack
}  

// valgrind?
