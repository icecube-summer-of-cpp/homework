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
}
