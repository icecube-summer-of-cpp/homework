//
//  e3.cpp
//  
//
//  Created by Isabelle Ansseau on 8/06/17.
//
//

#include "e3.hpp"
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream market ;
    market.open("market.txt");
    if (market.good()) {
        std::cout <<"voici le fichier \n";
        std::string line ;
        while(std::getline(market, line))
        {
            //std::cout << line[0]<<std::endl;
            //std::string b = "%";
            //std::string t = std::string(line[0]) ;
            if (line[0] =='%') {continue;} 
            std::cout << line << std::endl ;
	    break ;
        }
    } else {
        std::cout << "Fichier inexistant" ;
    }
    market.close();
    return 0 ;
}
