
#ifndef UNIQUEID
#define UNIQUEID

#include <unistd.h>     // for pid
#include <chrono>       // for time

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

class unique_id {
    
    private:
        static unsigned count_;
        static int process_;
        static std::chrono::_V2::system_clock::time_point time_;
        
        std::chrono::_V2::system_clock::time_point id_t_;
        int id_of_process_;
        int id_;
    
    public:
        // default constructor
        unique_id(): id_(++count_), id_t_(time_), id_of_process_(process_) { };
        
        // copy constructor
        unique_id(const unique_id& rhs) = default;
        
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
