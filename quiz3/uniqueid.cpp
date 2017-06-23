/* Ben Hokanson-Fasig
 * Summer of C++ - Quiz 3
 */

#include "uniqueid.hpp"


// Initialize counter
unsigned int unique_id::counter = 0;


// Default constructor of unique_id
unique_id::unique_id() : object_id(++counter) {}


// Getter for object_id
unsigned int unique_id::oid() const
{
    return object_id;
}


// Getter for process_id
int unique_id::pid() const
{
    return process_id;
}


// Comparison of unique_ids
bool unique_id::operator==(const unique_id& other) const
{
    return (object_id==other.oid() && process_id==other.pid());
}


// Stream output function for unique_id
std::ostream& operator<<(std::ostream& os, const unique_id& id)
{
    return os << id.process_id << "(" << id.object_id << "/" << id.counter << ")";
}


// int main()
// {
//     unique_id id1, id2, id3;
//     std::cout << "id1 = " << id1 << "\nid3 = " << id3 << std::endl;
//     std::cout << "id1==id1? " << (id1==id1?"True":"False") << std::endl;
//     std::cout << "id1==id2? " << (id1==id2?"True":"False") << std::endl;
//     return 0;
// }
