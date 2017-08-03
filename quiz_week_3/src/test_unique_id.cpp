// Summer of C++ 
// Quiz Week 3 
// Solution by: Rene Reimann

/*
 * Write a class that serves as a unique identifier for other objects. 
 * I should be able to use this identifier as a class member to use for comparisons.
 * 
 * The class should compare equal to copies of itself, but not to objects 
 * created at the same time, on the same machine, in different processes.
 * 
 * It should not be computationally expensive to create subsequent IDs 
 * in one process. (Hint: You can use two private members: one that is 
 * expensive to compute and one that's cheap to compute. 
 * Unique ID objects compare equal if the two members compare equal.)
 * 
 * Follow the "Rule of Six."
 * 
 * Below is an example of a typical use case
 */
 
#include "unique_id.hpp"
#include "particle.hpp"
#include <vector>
#include <cassert>

int main(){
    
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

}
