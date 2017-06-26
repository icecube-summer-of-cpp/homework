#ifndef UNIQUE_ID_UNIQUE_ID_HPP
#define UNIQUE_ID_UNIQUE_ID_HPP

#include <ostream>

class unique_id
{
    public:
        unique_id();

        unsigned int major() const {return major_;};
        unsigned int minor() const {return minor_;};

        bool operator==(const unique_id& other) const;
        bool operator!=(const unique_id& other) const;

    private:
        static unsigned int generated_;

        unsigned int major_;
        unsigned int minor_;
};

std::ostream& operator<<(std::ostream& os, const unique_id& id);

#endif
