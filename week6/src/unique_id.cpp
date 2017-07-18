#include "unique_id.hpp"

// initial initialization
// has to be in the source file, not in the header, because otherwise 
// initialization may happen multiple times, leading to linking errors
unsigned unique_id::count_ = 0;
int unique_id::process_ = ::getpid();
std::chrono::_V2::system_clock::time_point unique_id::time_ = std::chrono::system_clock::now();

// test unique_id

/*
 * constructor, assignment, move, destructor, comparison, getter, setters, tests, comments, printing, functionallity
 *
 *
 * UNIQUE_ID
 * ---------
 * + process (PID)
 * + host (IP/hostname/MAC)
 * + time  ns since epoch
 * + id    incremental number
 * 
 */
