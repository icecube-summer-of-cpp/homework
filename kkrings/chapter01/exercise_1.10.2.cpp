/**
 * Solution to exercise 1.10.2
 */

int main()
{
    // pointer to a character
    char c = 'a';
    char* cp = &c;

    // array of 10 integers (on the stack)
    const int size = 10;
    int a[size];

    for (int i = 0; i < size; ++i)
    {
        a[i] = i;
    }

    // pointer to an array of 10 integers
    // C-style array supports pointer arithmetics
    int* ap = a;

    // pointer to an array of character strings
    // assume character string refers to C-style string
    char* sp[] = {"hello", "world"};

    // pointer to a pointer to a character
    char** cpp = &cp;

    // integer constant
    const int i = 0;

    // pointer to an integer constant
    const int* ip = &i;

    // constant pointer to an integer
    int j = 0;
    int* const jp = &j;

    // array on the heap
    // do not release the memory to see its effect
    int* b = new int[size];
}
