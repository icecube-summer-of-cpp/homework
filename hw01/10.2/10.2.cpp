int main(int argc, char const *argv[])
{
    /*
    // Part A: Pointers and vars
    */
    char c = 'C';  // Single char
    char* c_ptr;  // Ptr to char

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Array of 10 ints

    int* arr_ptr = arr;  // Ptr to the int array

    char characters[] = {'A','B','C','D','E'};  // Array of chars
    char* characters_ptr = characters;  // Pointer to the char array

    char** c_ptr_ptr = &c_ptr;  // Ptr to the char ptr

    const int const_int = 1;  // Constant int
    int i = 2;  // Mutable int
    const int* int_ptr = &const_int;  // Ptr to const int
    int* const const_int_ptr = &i;  // Constant ptr to the int

    /*
    // Part B: Stack (fixed, c style) and Heap arrays (dynamically allocated)
    // Is that correct??
    */
    int stack_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int* heap_arr = new int[10];  // No other way to init?
    for(int i=0; i<10; ++i){
        heap_arr[i] = i;
    }

    return 0;
}