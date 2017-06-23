//
// Created by Frederik Lauber on 12.06.17.
//
#include <iostream>

//some stupid old style code so we can experiment with shared and unique ptrs and ressource management

struct val_chain{
    val_chain* previous=NULL;
    double val = 0;
};

val_chain* foo=NULL;
void addVal(double x){
  val_chain* tmp = new val_chain;
  tmp->previous = foo;
  tmp->val = x;
  foo = tmp;
}

double popVal(){
  val_chain* tmp = foo->previous;
  double res = foo->val;
  delete foo;
  foo = tmp;
  return res;
}

//int main(){
//  addVal(1.);
//  addVal(123.);
//  std::cout << popVal() << std::endl;
//  std::cout << popVal() << std::endl;
//  return 0;
//}