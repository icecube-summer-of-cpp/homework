/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 1.10.2
 * 1. Write the following declarations: pointer to a character, array of 10
 *    integers, pointer to an array of 10 integers, pointer to an array of
 *    character strings, pointer to pointer to a character, integer constant,
 *    pointer to an integer constant, constant pointer to an integer. Initialize
 *    all these objects.
 * 2. Make a small program that creates arrays on the stack (fixed-size arrays)
 *    and arrays on the heap (using allocation). Use valgrind to check what
 *    happens when you do not delete them correctly.
 */

#include <iostream>
#include <memory>


void print_array(int size, int array[])
{
    for (int i=0; i<size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// void print_array(int size, std::shared_ptr<int[]> array)
// {
//     for (int i=0; i<size; ++i) {
//         std::cout << array[i] << " ";
//     }
//     std::cout << std::endl;
// }


int main()
{
    // Part 1:
    std::unique_ptr<char> char_ptr(new char); // pointer to character
    int int_array[10] = {1,2,3,4,5,6,7,8,9,10}; // array of 10 integers
    std::unique_ptr<int[]> int_array_ptr(new int[10]); // pointer to array of 10 integers
    std::unique_ptr<char[]> char_array_ptr(new char[10]); // pointer to an array of characters
    std::unique_ptr<std::unique_ptr<char>> char_ptr_ptr(new std::unique_ptr<char>); // pointer to pointer to a character
    const int cint = 7; // constant integer
    std::unique_ptr<const int> cint_ptr(new int); // pointer to integer constant
    const std::unique_ptr<int> int_cptr(new int); // constant pointer to integer

    // Assign values as a check
    *char_ptr = 'a';
    for (int i=0; i<10; ++i) {
        int_array_ptr[i] = int_array[i]+10;
        char_array_ptr[i] = 'b';
    }
    *int_cptr = 8;

    // Print values to make sure everything is done properly
    std::cout << *char_ptr << std::endl;
    print_array(10, int_array);
    // TODO: Figure out how to use print_array with this
    // Update: it's not easy
    for (int i=0; i<10; ++i) {
        std::cout << int_array_ptr[i] << " ";
    }
    std::cout << std::endl;
    for (int i=0; i<10; ++i) {
        std::cout << char_array_ptr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << cint << std::endl;
    std::cout << *cint_ptr << std::endl;
    std::cout << *int_cptr << std::endl;


    // Part 2:
    
}
