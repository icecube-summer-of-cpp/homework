#include <unistd.h>
#include "unique_id.hpp"

unsigned int unique_id::generated_ = 0;

unique_id::unique_id() : major_(::getpid()), minor_(0)
{
    minor_ = generated_;
    generated_++;
}

bool unique_id::operator==(const unique_id& other) const
{
    return major_ == other.major() && minor_ == other.minor();
}

bool unique_id::operator!=(const unique_id& other) const
{
    return major_ != other.major() || minor_ != other.minor();
};

std::ostream& operator<<(std::ostream& os, const unique_id& id)
{
    return os << id.major() << '(' << id.minor() << ')';
}
