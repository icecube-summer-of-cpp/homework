/* Ben Hokanson-Fasig
 * Person class and derived classes
 */

#include "people.hpp"


void person::set_name(const std::string& n) {
    name = n;
}


std::string person::get_name() const {
    return name;
}


void person::my_name() const {
    std::cout << "My name is " << name << std::endl;
}


void person::all_info() const {
    my_name();
    my_infos();
}



void student::my_infos() const {
    std::cout << "  I passed the following grades: " << passed << std::endl;
}



void mathematician::my_infos() const {
    std::cout << "  I proved: " << proved << std::endl;
}



void math_student::my_infos() const {
    student::my_infos();
    mathematician::my_infos();
}


void math_student::all_info() const {
    my_name();
    my_infos();
}