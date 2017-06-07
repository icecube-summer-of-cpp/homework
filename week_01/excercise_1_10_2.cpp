/**
 * Summer of C++ - 2017
 * excercise_1_10_2.cpp
 * 
 *
 * @author Mirco Huennefeld
 * @version 1.0 06/07/17
 */


// include necessary libraries
#include <iostream>
#include <string>


void print_usage(char* argv[]){
    // Tell the user how to run the program
    std::cerr << "\nUsage: " << argv[0] << " MemType\n";
    std::cerr << "\n       Possible values for MemType are:\n";
    std::cerr << "         '0': creates arrays on stack.\n";
    std::cerr << "         '1': creates arrays on heap.\n";
    std::cerr << "         '2': creates arrays on heap without deleting.\n\n";
}


/**
 * @brief Test array allocation on stack
 * @param iterations number of iterations to perform
 * @param size size of the array to allocate
 */
void test_stack( int iterations=1000, int size=10){
    for( int i = 0; i < iterations ; i++){
        double array[size];
    }
}

/**
 * @brief Test array allocation on heap
 * @param del bool
 *            true: free memory
 *            false: do not free memory
 * @param iterations number of iterations to perform
 * @param size size of the array to allocate
 */
void test_heap(bool del, int iterations=1000, int size=10){
    for( int i = 0; i < iterations ; i++){
        double* array = new double[size];
        if(del){
            delete[] array;
        }
    }
}


int main(int argc, char* argv[])
{
    // Part 1: Variable declaration and initialisation

    // pointer to character
    char* pchar = nullptr;

    // array of 10 integers
    int array[10];

    for(int i=0; i<10; i++){
        array[i] = 0;
    }

    // pointer to an array of 10 integers
    int* p_array = array; // alertnatively &array[0]

    // pointer to an array of character strings
    std::string* p_string_array = nullptr; // string
    char** p_char_array = nullptr; // char*

    // pointer to pointer to a character
    char** p_p_char = nullptr;

    // integer constant
    const int const_int = 0;

    // pointer to an integer constant
    const int* p_const_int = & const_int;
    int const * p_const_int2 = & const_int;

    // constant pointer to an integer
    int* const const_p_int = nullptr;




    // Part 2

    // Check the number of parameters
    if (argc != 2) {
        print_usage(argv);
        return 1;
    }

    switch(argv[1][0]){

        // Test on stack
        case '0' : std::cout << "Now testing Stack...\n";
                    test_stack();
                    break;

        // Test on heap with freeing memory
        case '1' : std::cout << "Now testing Heap...\n";
                   test_heap(true);
                   break;

        // Test on heap without freeing memory
        case '2' : std::cout << "Now testing heap with leak...\n";
                   test_heap(false);
                   break;

        default : print_usage(argv);
                  return 1;
    }


    return 0;
}


/*

-------------------
Test with valgrind:
-------------------


stack:
----------------------------------------------
valgrind --tool=memcheck ./excercise_1_10_2 0
----------------------------------------------
==5083== Memcheck, a memory error detector
==5083== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5083== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==5083== Command: ./excercise_1_10_2 0
==5083== 
Now testing Stack...
==5083== 
==5083== HEAP SUMMARY:
==5083==     in use at exit: 0 bytes in 0 blocks
==5083==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==5083== 
==5083== All heap blocks were freed -- no leaks are possible
==5083== 
==5083== For counts of detected and suppressed errors, rerun with: -v
==5083== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


heap with deletion:
----------------------------------------------
valgrind --tool=memcheck ./excercise_1_10_2 1
----------------------------------------------
==5111== Memcheck, a memory error detector
==5111== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5111== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==5111== Command: ./excercise_1_10_2 1
==5111== 
Now testing Heap...
==5111== 
==5111== HEAP SUMMARY:
==5111==     in use at exit: 0 bytes in 0 blocks
==5111==   total heap usage: 1,000 allocs, 1,000 frees, 80,000 bytes allocated
==5111== 
==5111== All heap blocks were freed -- no leaks are possible
==5111== 
==5111== For counts of detected and suppressed errors, rerun with: -v
==5111== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


heap without deletion:
----------------------------------------------
valgrind --tool=memcheck ./excercise_1_10_2 2
----------------------------------------------
==5119== Memcheck, a memory error detector
==5119== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5119== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==5119== Command: ./excercise_1_10_2 2
==5119== 
Now testing heap with leak...
==5119== 
==5119== HEAP SUMMARY:
==5119==     in use at exit: 80,000 bytes in 1,000 blocks
==5119==   total heap usage: 1,000 allocs, 0 frees, 80,000 bytes allocated
==5119== 
==5119== LEAK SUMMARY:
==5119==    definitely lost: 80,000 bytes in 1,000 blocks
==5119==    indirectly lost: 0 bytes in 0 blocks
==5119==      possibly lost: 0 bytes in 0 blocks
==5119==    still reachable: 0 bytes in 0 blocks
==5119==         suppressed: 0 bytes in 0 blocks
==5119== Rerun with --leak-check=full to see details of leaked memory
==5119== 
==5119== For counts of detected and suppressed errors, rerun with: -v
==5119== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


*/