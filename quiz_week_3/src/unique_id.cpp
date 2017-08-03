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

// initial initialization
// has to be in the source file, not in the header, because otherwise 
// initialization may happen multiple times, leading to linking errors
unsigned unique_id::count_ = 0;
int unique_id::process_ = ::getpid();
std::chrono::_V2::system_clock::time_point unique_id::time_ = std::chrono::system_clock::now();
