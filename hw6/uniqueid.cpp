/* Ben Hokanson-Fasig
 * Summer of C++ - Quiz 3
 */

#include "uniqueid.hpp"


// Initialize counter
unsigned int UniqueID::counter = 0;


// Default constructor of UniqueID
UniqueID::UniqueID() : object_id(++counter) {}


// Getter for object_id
unsigned int UniqueID::oid() const
{
    return object_id;
}


// Getter for process_id
int UniqueID::pid() const
{
    return process_id;
}


// Comparison of UniqueIDs
bool UniqueID::operator==(const UniqueID& other) const
{
    return (object_id==other.oid() && process_id==other.pid());
}


// Stream output function for UniqueID
std::ostream& operator<<(std::ostream& os, const UniqueID& id)
{
    return os << id.process_id << "-" << id.object_id;
}


// int main()
// {
//     UniqueID id1, id2, id3;
//     std::cout << "id1 = " << id1 << "\nid3 = " << id3 << std::endl;
//     std::cout << "id1==id1? " << (id1==id1?"True":"False") << std::endl;
//     std::cout << "id1==id2? " << (id1==id2?"True":"False") << std::endl;
//     return 0;
// }
