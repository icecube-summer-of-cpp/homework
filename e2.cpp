//
//  e2.cpp
//  
//
//  Created by Isabelle Ansseau on 8/06/17.
//
//

#include "e2.hpp"
#include <iostream>
#include <valarray>

int main()
{
    //pointer to a character
    std::unique_ptr<char> a {new char} ;
    a = 7 ;
    //array of 10 integers
    int b[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} ;
    //pointer to an array of 10 integer
    std::unique_ptr<int> c {new int[10]} ;
    c ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9} ;
    //pointer to an array of character strings
    std::unique_ptr<char> d {new char[5]} ;
    d ={"a", "b", "c", "d", "e"} ;
    //pointer to pointer to a character
    std::shared_ptr<std::string> e(new std::string);
    e = "a";
    //integer constant
    const int f =2;
    //pointer to an integer constant
    std::unique_ptr<int> g {const int} ;
    //constant pointer to an integer
    std::unique_ptr<const int> f {int} ;
    
    //small program thant create arrays on the stack and on the heap. Use Valgrind to check what happens when you do not delete them correctly
    
    std::valarray<float> ;
    
    return 0
}
