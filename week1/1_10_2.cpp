#include <memory>

int main() {
    /*
     * pointer to a character:
     */
    char single_char = 'n';
    // raw pointer
    char* p_char = &single_char;
    // smart pointer
    auto p_smart_char = std::make_shared<char>(single_char);

    int array_int[10];
    for (int i=0; i < 10; i++) {
        array_int[i] = i*2;
    }
    /*
     * array of 10 integers:
     */
    // raw pointer
    int* p_array_int = array_int;
    // smart pointer to the array
    auto p_smart_array_int = std::make_shared<int>(*array_int);
    // smart pointer to pointer
    auto p_smart_p_array_int = std::make_shared<int*>(array_int);


    /*
     * pointer to  an  array   of  character   strings
     */
    char array_strings[] = {'n', 'a', 'm', 'e'};
    // raw pointer
    char* p_array_strings = array_strings;

    /*
     * pointer to pointer to a character
     */
    char single_char_2 = 'c';
    char* p_single_char_2 = &single_char_2;
    char** p_p_single_char_2 = &p_single_char_2;

    /*
     * const int
     */
    const int i = 42;
    const int * p_i = &i;

    /*
     * constant pointer to an integer
     */
    int j = 43;
    int * const p_j = &j;


    int stack_array[1000];
    int *heap_array = new int[100];

    // delete [] my_heap_array;
    return 0;
}
