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
 * 2. Make a small program that creates arrays on the stack (fixed-size 
 *    arrays) and arrays on the heap (using allocation). Use valgrind to
 *    check what happens when you do not delete them correctly.
 */

#include <iostream>
#include <memory>

void define_simple_pointer(){
    // pointer to a character
    //char * p1 = new char('a');
    char * p1;
    p1 = new char('a');
    std::cout << p1 << " " << *p1 << std::endl;
    p1 = new char('b');
    std::cout << p1 << " " << *p1 << std::endl;
    *p1 = 'c';
    std::cout << p1 << " " << *p1 << std::endl;
    
    // array of 10 integers
    int a1[10] = {1,2,3,4,5,6,7,8,9,0};
    
    std::cout << a1 << " " << *a1 << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "   " << a1[i] << std::endl;}
    
    // pointer to an array of 10 integers
    
    int * p2 = new int[10];                     // can it be directly initialized?
    for (unsigned i=0; i<10; ++i){ p2[i]=i*2;}  // initiallizing
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
    p5 = new const int(3);
    std::cout << p5 << " "<< *p5 << std::endl;
    
    // constant pointer to an integer
    int * const p6 = new int(22);
    std::cout << p6 << " "<< *p6 << std::endl;
    //p6 = new int(3); // not allowed
    std::cout << p6 << " "<< *p6 << std::endl;
    *p6 += 1;
    std::cout << p6 << " "<< *p6 << std::endl;
    
    // Initialize all these objects.
    
    delete p1, p2, p3, p4, p5, p6;
}

void define_smart_pointer(){
    // pointer to a character
    std::shared_ptr<char> p1 = std::make_shared<char>('a');
    std::cout << "P1: " << p1 << " *P1: " << *p1 << std::endl;
    
    // array of 10 integers
    // pointer to an array of 10 integers
    // pointer to an array of character strings
    // pointer to pointer to a character
    // interger constant
    // pointer to an integer constant
    // constant pointer to an integer
}

int main(){
    define_simple_pointer();
    //define_smart_pointer();
    
    /*
    
    //std::shared_ptr<char> p1 = std::make_shared<char>();
    //*p1 = 'a';
    std::cout << "P1: " << " *P1: " << p1 << std::endl;
        
    // array of 10 integers
    int a1[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::cout << "a1: " << a1 << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "    a1[" << i << "]: " << a1[i] << std::endl;}

    // pointer to an array of 10 integers    
    std::unique_ptr<int[]> p2{new int[10]}; // how to do with shared_ptr // why can't initialize with  {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
    for (unsigned i=0; i<10; ++i){p2[i] = i+2;}
    std::cout << "P2.get(): " << p2.get() << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "    P2.get()[" << i << "]: " << p2.get()[i] << std::endl;}
    
    // pointer to an array of character strings
    std::unique_ptr<std::string[]> p3{new std::string[10]}; // how to do with shared_ptr 
    for (unsigned i=0; i<10; ++i){ p3[i] = ('a'+i);}
    std::cout << "*P3: " << p3.get() << std::endl;
    for (unsigned i=0; i<10; ++i){ std::cout << "    P3[" << i << "]: " << p3[i] << std::endl;}
    
    // pointer to pointer to a character
    std::shared_ptr<std::shared_ptr<char>> p4 = std::make_shared<std::shared_ptr<char>>(); //{new char}; //
    **p4 = 'b';
    
    std::cout << "P4: " << p4 << " *P4: " << *p4  << std::endl; // << " *P4: " << *p4 << " P4->get(): " << p4->get()
    **p4 = 'b';
    
    // interger constant
    const int c1 = 15;
    std::cout << "c1: " << c1 << std::endl;
    */
    //std::shared_ptr<const int> p5{new const int 15};// = std::make_shared<const int>();
    //std::cout << "p5: " << p5 << "p5*: " << p5* << std::endl;
    /*

    
     
    // pointer to an integer constant
    int *pointer_to_an_integer_constant = const 15 ; 

    // constant pointer to an integer
    const int *constant_pointer_to_an_integer = 15;



    */
    return 0;
}
