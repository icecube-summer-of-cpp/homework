/** 
 *  Summer of C++
 *  Week 1, Exercise 1.10.1
 *  @author: Federica Bradascio
 *
 *  Write a program that asks input from the keyboard and 
 *  print the result on the screen and writes it to a file.
 */

#include <iostream>
#include <fstream>

int main ()
{
  int age;
  std::cout << "What is your age?" << std::endl;
  std::cin >> age;
  std::cout << "You are " << age << " years old!" << std::endl;

  std::ofstream outfile("ex1.10.1_output.txt");
  if (outfile.is_open()) {
    outfile << "What is your age?\nMy age is "
  	    << age << "."
  	    << std::endl;
    outfile.close();
  }
  else {
    std::cout << "The file could not be opened!"
  	      << std::endl;
  }
  return 0;
}
