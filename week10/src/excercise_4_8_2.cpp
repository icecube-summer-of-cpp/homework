// Summer of C++ 
// Quiz Week 10
// Solution by: Rene Reimann

/*
 * 
 * 4.8.2
 * 
 * STL Container
 * 
 * Create a std::map for phone numbers; i.e., map from a string to an unsigned long. Fill the 
 * map with at least four entries. Search for an existing and a non-existing name. Also search
 * for an existing and a non-existing number.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

template<typename T>
void find_number(T map, std::string name){
    auto entry = map.find(name);
    if (entry != end(map))
        std::cout << entry->second << std::endl;
    else
        std::cout << "Not found" << std::endl;
};

template<typename F>
class check_num{
    public:
        check_num(unsigned long number): number(number) {};
        
        bool operator()(const F& entry) const {
            return entry.second == number;
        }
        
    private:
        unsigned long number;
};

template<typename T>
void find_name(T map, unsigned long number){
    auto entry = std::find_if(begin(map), end(map), check_num<decltype(*begin(map))>(number));
    if (entry != end(map))
        std::cout << entry->first << std::endl;
    else
        std::cout << "Not found" << std::endl;
};

int main (int argc, char **argv) 
{
    std::map<std::string, unsigned long> phone_book = {{"home", 2131511125}, 
                                                       {"mobile", 1788499785}, 
                                                       {"office", 2418027297}, 
                                                       {"Herbert", 49771127}};
                                                       
    find_number(phone_book, "Herbert");
    find_number(phone_book, "Hermann");
    
    find_name(phone_book, 2131511125);
    find_name(phone_book, 123456789);

    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
