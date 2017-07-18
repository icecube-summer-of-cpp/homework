#include <iostream>
#include <string>
#include <memory>
#include <vector>
// the thing to do is
// valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./arrays_and_pointers_2
// however how to interpret the output, I don't know...
int main()
{
    //while(true)
    //{
        // fixed-size arrays go on the heap (whatever that means!)
        int fixed[64];
        // dynamically allocated arrays go on the stack (yeah what the hell is this)
        int* dynamic = new int[64];
        while(true); //I just want to sleep forever / Never see tomorrow / Or lead or follow
    //}
}