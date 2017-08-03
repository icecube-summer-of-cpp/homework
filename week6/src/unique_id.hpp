#ifndef UNIQUEID
#define UNIQUEID

#include <unistd.h>     // for pid
#include <chrono>       // for time
#include <ctime>
#include <iostream>
#include "gtest/gtest.h"

/*
 *
 * UNIQUE_ID
 * ---------
 * Makes individual ID for ...
 */

class unique_id {
    
    public:
        // constructors
        unique_id();
        unique_id(const unique_id&) = default;
        unique_id(unique_id&&) = default;
        
        // assignments
        unique_id& operator=(const unique_id&) = default;
        unique_id& operator=(unique_id&&) = delete;
        
        // destructor
        ~unique_id() = default;        
    
    private:
        static unsigned count_;
        static int process_;
        static std::chrono::_V2::system_clock::time_point time_;
        
        int id_;
        int id_of_process_;
        std::chrono::_V2::system_clock::time_point id_t_;
        
    friend std::ostream& operator <<(std::ostream&, const unique_id&);
    friend bool operator==(const unique_id&, const unique_id&);
};

// printing
std::ostream& operator <<(std::ostream&, const unique_id&);

// comparisons
bool operator==(const unique_id&, const unique_id&);
bool operator!=(const unique_id&, const unique_id&);
#endif
