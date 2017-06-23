/* Ben Hokanson-Fasig
 * Summer of C++ - Quiz 3
 */

// Include guard
#ifndef __UNIQUEID_HEADER_INCLUDED__
#define __UNIQUEID_HEADER_INCLUDED__

#include <iostream>
#include <unistd.h>
// #include <sys/types.h>

class unique_id
{
    public:
        // Default constructor
        unique_id();

        // Copy constructor
        unique_id(const unique_id&) = default;

        // Move constructor
        unique_id(unique_id&&) = default;

        // Copy assignment
        unique_id& operator=(const unique_id&) = default;

        // Move assignment
        unique_id& operator=(unique_id&&) = default;

        // Destructor
        ~unique_id() = default;

        // Getter for object_id
        unsigned int oid() const;

        // Getter for process_id
        int pid() const;

        // Comparison
        bool operator==(const unique_id& other) const;


    // Allow stream output to access private members
    friend std::ostream& operator<<(std::ostream& os, const unique_id& id);

    private:
        static unsigned int counter; // Increments for each object created
        const unsigned int object_id; // Set to counter value when object is instantiated
        const int process_id = ::getpid(); // Set process id automatically
        
};

// Stream output function for unique_id
std::ostream& operator<<(std::ostream& os, const unique_id& id);


#endif
