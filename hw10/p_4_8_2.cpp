/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 4.8.2
 * Create a std::map for phone numbers; i.e., map from a string to an unsigned
 * long. Fill the map with at least four entries. Search for an existing and a
 * non-existing name. Also search for an existing and a non-existing number.
 */




#include <algorithm>
#include <iostream>
#include <string>
#include <map>


std::ostream& print_phone_number(std::ostream& os, unsigned long number)
{
    if (number>999999)
    {
        unsigned long prefix = number/10000;
        unsigned long suffix = number-prefix*10000;
        return os << prefix << "-" << suffix;
    }
    else
    {
        return os << number;
    }
}


void display_phone_number(std::string key, std::map<std::string,unsigned long>& phone_number_map)
{
    std::cout << key << "'s phone number: ";
    print_phone_number(std::cout, phone_number_map[key]);
    std::cout << std::endl;
}


void dial(unsigned long number, std::map<std::string,unsigned long>& phone_number_map)
{
    std::cout << "Dialing ";
    print_phone_number(std::cout, number);
    std::cout << "... ";
    auto it = std::find_if(phone_number_map.begin(),phone_number_map.end(),
    [number](std::pair<std::string,unsigned long> p){return p.second==number;});
    if (it==phone_number_map.end())
    {
        std::cout << "No answer" << std::endl;
    }
    else
    {
    std::cout << "Hello, this is " << it->first << std::endl;
    }
}

int main()
{
    std::map<std::string,unsigned long> phones = 
    {{"Nobody",5555555}, {"Jenny",8675309}, {"Emergency Services",911}, {"The Count",1234567}};

    display_phone_number("Nobody",phones);
    display_phone_number("Jenny",phones);
    display_phone_number("Emergency Services",phones);
    display_phone_number("The Count",phones);
    display_phone_number("Ben",phones);

    dial(8675309,phones);
    dial(911,phones);
    dial(0,phones);
    dial(1,phones);
}