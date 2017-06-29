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

#ifndef UNIQUEID
#define UNIQUEID

#include <unistd.h>     // for pid
#include <chrono>       // for time
// #include <limits.h>    // for hostname

class unique_id {
    
    private:
        static unsigned count_;
        
        std::chrono::_V2::system_clock::time_point id_t_;
        int id_of_process_;
        int id_;
        // char id_hostname_[HOST_NAME_MAX];
    
    public:
        // default constructor
        unique_id(): id_(++count_), id_t_(std::chrono::system_clock::now()), id_of_process_(::getpid()) { };
        // gethostname(id_hostname_, HOST_NAME_MAX);
        
        // copy constructor
        unique_id(const unique_id& rhs) = default;    
        //unique_id(const unique_id& rhs): id_(rhs.id_), id_t_(rhs.id_t_), id_of_process_(rhs.id_of_process_){};    
        
        // move constructor
        unique_id(unique_id&& src) = default;
        
        // copy assignment operator
        unique_id& operator=(const unique_id&) = default;
        
        // move assignment operator
        unique_id& operator=(unique_id&& src) = delete;
        
        // A destructor
        ~unique_id() = default;        
        
    friend inline bool operator==(const unique_id& lhs, const unique_id& rhs);
};

// free function for comparison
inline bool operator==(const unique_id& lhs, const unique_id& rhs) { 
    return (lhs.id_ == rhs.id_) && (lhs.id_of_process_ == rhs.id_of_process_) && (lhs.id_t_ == rhs.id_t_); 
};

#endif
