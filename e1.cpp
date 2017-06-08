//
//  e1.cpp
//  
//
//  Created by Isabelle Ansseau on 8/06/17.
//
//

#include "e1.hpp"
#include <iostream>
#include <fstream>

int main ()
{
    std::cout << "Quel est votre age ?" << std::endl ;
    int age ;
    std::cin >> age ;
    std::cout << "Vous avez " << age << " ans !" << std::endl ;
    std::ofstream ages ;
    ages.open("ages.txt") ;
    ages << age << std::endl ;
    ages.close() ;
    return 0 ;
}
