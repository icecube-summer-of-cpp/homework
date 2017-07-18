#include <iostream>
#include <string>
#include <memory>
#include <vector>

int main()
{
    // a) pointer to a character
    char* a = new char{'a'};// use new => have to delete this! else memory leak
    auto a_modern = std::make_unique<char>('a');// modern C++ = no worries
    //without auto
    std::unique_ptr<char> a_more_explicit(new char('a'));
    
    // b) array of 10 integers
    int b[] = {0,1,2,3,4,5,6,7,8,9};
    std::vector<int> b_modern = {0,1,2,3,4,5,6,7,8,9};
    
    // c) pointer to an array of 10 integers
    int* c = new int[10]{0,1,2,3,4,5,6,7,8,9}; // I don't understand this (!)
    auto c_modern = std::make_unique<std::vector<int>>(std::vector<int>{0,1,2,3,4,5,6,7,8,9});
    
    // d) pointer to an array of character strings
    char* d = new char[2]{'a','b'};
    std::string* d_string = new std::string[2]{"Zeppelin","rules"};
    // pointer to (modern): auto x = std::make_unique<type>(literal);
    // (literal can also be variable)
    // pointer to array (modern): type    = std::vector<type>
    //                            literal = std::vector<type>{lit,lit,lit}
    auto d_modern = std::make_unique<std::vector<char>>(std::vector<char>{'c','d'});    
    auto d_modern_string = std::make_unique<std::vector<std::string>>(std::vector<std::string>{"Nuke","the","wales"});
    
    // e) pointer to pointer to a character
    char** e = new char*{new char{'e'}};
    auto e_modern = std::make_unique<std::unique_ptr<char>>(std::make_unique<char>('e'));
    
    // f) integer constant
    const int f = 42;
    
    // g) pointer to an integer constant
    const int* g = new const int(f); // yep this has to be read backwards
    auto g_modern = std::make_unique<const int>(f); // much more intuitive here
    
    // h) constant pointer to an integer
    int* const h = new int(23); // yep this has to be read backwards
    const auto h_modern = std::make_unique<int>(23); //whereas this makes so much more sense

}