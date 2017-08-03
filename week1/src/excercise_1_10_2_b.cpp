// Summer of C++ 
// Homework Week 1 
// Excercise 1.10.2 part 2 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

/*
 * 2. Make a small program that creates arrays on the stack (fixed-size 
 *    arrays) and arrays on the heap (using allocation). Use valgrind to
 *    check what happens when you do not delete them correctly.
 */

#include <iostream>
#include <memory>

int main(){
    int my_stack_array[100];
    int * my_heap_array = new int[100];

    delete [] my_heap_array;
    
    /* 
     * If delete is commented out we get:
     * valgrind --leak-check=yes ./excercise_1_10_2_b 
        ==19888== Memcheck, a memory error detector
        ==19888== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
        ==19888== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
        ==19888== Command: ./excercise_1_10_2_b
        ==19888== 
        ==19888== 
        ==19888== HEAP SUMMARY:
        ==19888==     in use at exit: 400 bytes in 1 blocks
        ==19888==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
        ==19888== 
        ==19888== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
        ==19888==    at 0x4C2B800: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
        ==19888==    by 0x4008E1: main (excercise_1_10_2_b.cpp:23)
        ==19888== 
        ==19888== LEAK SUMMARY:
        ==19888==    definitely lost: 400 bytes in 1 blocks
        ==19888==    indirectly lost: 0 bytes in 0 blocks
        ==19888==      possibly lost: 0 bytes in 0 blocks
        ==19888==    still reachable: 0 bytes in 0 blocks
        ==19888==         suppressed: 0 bytes in 0 blocks
        ==19888== 
        ==19888== For counts of detected and suppressed errors, rerun with: -v
        ==19888== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

    
    If delete is not commented out we get:
    * valgrind --leak-check=yes ./excercise_1_10_2_b 
        ==19931== Memcheck, a memory error detector
        ==19931== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
        ==19931== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
        ==19931== Command: ./excercise_1_10_2_b
        ==19931== 
        ==19931== 
        ==19931== HEAP SUMMARY:
        ==19931==     in use at exit: 0 bytes in 0 blocks
        ==19931==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
        ==19931== 
        ==19931== All heap blocks were freed -- no leaks are possible
        ==19931== 
        ==19931== For counts of detected and suppressed errors, rerun with: -v
        ==19931== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)    
    */
}
