/* Ben Hokanson-Fasig
 * Summer of C++ - Quiz 3
 */

// Include guard
#ifndef __UNIQUEID_HEADER_INCLUDED__
#define __UNIQUEID_HEADER_INCLUDED__

#include <iostream>
#include <unistd.h>
// #include <sys/types.h>

class UniqueID
{
    public:
        // Default constructor
        UniqueID();

        // Copy constructor
        UniqueID(const UniqueID&) = default;

        // Move constructor
        UniqueID(UniqueID&&) = default;

        // Copy assignment
        UniqueID& operator=(const UniqueID&) = default;

        // Move assignment
        UniqueID& operator=(UniqueID&&) = default;

        // Destructor
        ~UniqueID() = default;

        // Getter for object_id
        unsigned int oid() const;

        // Getter for process_id
        int pid() const;

        // Comparison
        bool operator==(const UniqueID& other) const;


    // Allow stream output to access private members
    friend std::ostream& operator<<(std::ostream& os, const UniqueID& id);

    private:
        static unsigned int counter; // Increments for each object created
        const unsigned int object_id; // Set to counter value when object is instantiated
        const int process_id = ::getpid(); // Set process id automatically
        
};

// Stream output function for UniqueID
std::ostream& operator<<(std::ostream& os, const UniqueID& id);


#endif
