// Summer of C++ 
// Homework Week 6 
// Solution by: Rene Reimann

/*
 * 
 * Write a particle base class and a sim_particle and reco_particle derived classes. 
 * Along the way you'll probably want to implement direction and position classes. 
 * The unique_id class will likely come in handy as well.
 * 
 */

#include "unique_id.hpp"
#include "particle.hpp"
#include "four_vector.hpp"
#include "gtest/gtest.h"



int main (int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    //z = {0, 1, 2};
    //std::cout << z << std::endl;
    
    /*
    particle p1;
    particle p2;
   
    p1.set_energy(1000);
    p2.set_energy(1000);
   
    // p1 and p2 are not the same particle even if their properties are different.
    assert(p1 != p2);
   
    unique_id test_id(p1.id()); // need to be able to copy them and compare later
   
    std::vector<particle> particle_list = {p1, p2};
   
    // i should be able to put them in containers and compare as expected
    assert( test_id == particle_list.front().id() );
    */
}
