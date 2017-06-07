// Summer of C++ 
// Homework Week 1 
// Excercise 1.10.2 part 1 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

/*
 * 1. Write the following declarations:
 *      pointer to a character
 *      array of 10 integers
 *      pointer to an array of 10 integers
 *      pointer to an array of character strings
 *      pointer to pointer to a character
 *      interger constant
 *      pointer to an integer constant
 *      constant pointer to an integer
 *    Initialize all these objects.
 */

#include <iostream>
#include <memory>

void define_simple_pointer(){
    
    // pointer to a character
    //char * p1 = new char('a');
    char * p1;
    p1 = new char('a');                                                 
    std::cout << p1 << " " << *p1 << std::endl;
    //p1 = new char('b');                                               // leads to mem-leak, L.26 not deleted
    std::cout << p1 << " " << *p1 << std::endl;
    //*p1 = 'c';                                                        // leads to mem-leak, L.28 not deleted
    std::cout << p1 << " " << *p1 << std::endl;
    
    // array of 10 integers
    int a1[10] = {1,2,3,4,5,6,7,8,9,0};
    std::cout << a1 << " " << *a1 << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "   " << a1[i] << std::endl;}
    
    // pointer to an array of 10 integers
    int * p2 = new int[10];                                             // can it be directly initialized?
    for (unsigned i=0; i<10; ++i){ p2[i]=i*2;}  
    std::cout << p2 << " " << *p2 << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "   " << p2[i] << std::endl;}
    
    // pointer to an array of character strings
    std::string * p3 = new std::string[10];                             
    for (unsigned i=0; i<10; ++i){ p3[i]="Hello"+std::to_string(i);}
    std::cout << p3 << " " << *p3 << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "   " << p3[i] << std::endl;}
    
    // pointer to pointer to a character
    char *ptemp = new char('d');
    char **p4 = &ptemp;
    std::cout << p4 << " " << *p4 << std::endl;
    
    // interger constant
    const int c1 = 15;
    std::cout << c1 << std::endl;
     
    // pointer to an integer constant
    const int * p5 = new const int(14);
    std::cout << p5 << " "<< *p5 << std::endl;
    // p5 = new const int(3);                                           // this leads to a memory leak because 
    // std::cout << p5 << " "<< *p5 << std::endl;                       // the const int created in L 62 is not deleted
    
    // constant pointer to an integer
    int * const p6 = new int(22);                                       
    std::cout << p6 << " "<< *p6 << std::endl;
    //p6 = new int(3); // not allowed
    std::cout << p6 << " "<< *p6 << std::endl;
    *p6 += 1;
    std::cout << p6 << " "<< *p6 << std::endl;
    
    // Initialize all these objects.

    delete p1;    
    delete [] p2;
    delete [] p3;
    delete *p4, p4; // we must first delete the pointer on the char before we delete the pointer to the pointer
    delete p5;
    delete p6;
}

void define_smart_pointer(){
    // pointer to a character
    std::shared_ptr<char> p1 = std::make_shared<char>('a');
    std::cout << "P1: " << p1 << " *P1: " << *p1 << std::endl;
    
    // array of 10 integers
    int a1[] = {1,2,3,4,5,6,7,8,9,0};
    std::cout << a1 << " " << *a1 << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "   " << a1[i] << std::endl;}
    
    // pointer to an array of 10 integers
    std::unique_ptr<int[]> p2{new int[10]};
    for (unsigned i=0; i<10; ++i){ p2[i] = 2*i; }
    for (unsigned i=0; i<10; ++i){ std::cout << "   " << p2[i] << std::endl;}
    
    // pointer to an array of character strings
    std::unique_ptr<std::string[]> p3{new std::string[10]};  
    for (unsigned i=0; i<10; ++i){ p3[i] = ('a'+i);}
    for (unsigned i=0; i<10; ++i){ std::cout << "    P3[" << i << "]: " << p3[i] << std::endl;}
    
    // pointer to pointer to a character
    std::shared_ptr<char> p_temp = std::make_shared<char>('g');
    std::shared_ptr<std::shared_ptr<char>> p4 = std::make_shared<std::shared_ptr<char>>(p_temp);
    std::cout << "P4: " << p4 << " *P4: " << *p4 << " **P4: " << **p4  << std::endl;
    
    // interger constant
    const int c1 = 15;
    std::cout << "c1: " << c1 << std::endl;
    
    // pointer to an integer constant
    std::shared_ptr<const int> p5 = std::make_shared<const int>(15);
    std::cout << "*p5: " << *p5 << std::endl;
    
    // constant pointer to an integer
    const std::shared_ptr<int> p6 = std::make_shared<int>(16);
    std::cout << "*p6: " << *p6 << std::endl;
    *p6 += 1;
    std::cout << "*p6: " << *p6 << std::endl;
    // p6 = std::make_shared<int>(18); // not allowed
}

int main(){
    define_simple_pointer();
    define_smart_pointer();

    return 0;
}
