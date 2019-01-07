#ifndef POKEBALL_UNIQUE_ID_HPP
#define POKEBALL_UNIQUE_ID_HPP

#include <ostream>

/**
 * @brief Unique particle ID
 *
 * All generated particles, both simulated and reconstructed, should be
 * uniquely identifiable. This is realized via a major and minor unique
 * ID. The major ID corresponds to the process ID. The minor ID is set
 * via a counter that is increased every time a new object is
 * constructed.
 */
class unique_id
{
    public:
        unique_id();

        unique_id(const unique_id&) = default;
        unique_id(unique_id&&) = default;

        ~unique_id() = default;

        unique_id& operator=(const unique_id&) = default;
        unique_id& operator=(unique_id&&) = default;

        bool operator==(const unique_id& other) const;
        bool operator!=(const unique_id& other) const;

        /**
         * @return Major ID
         */
        unsigned int major() const {return major_;};

        /**
         * @return Minor ID
         */
        unsigned int minor() const {return minor_;};

    private:
        static unsigned int generated_;
        unsigned int major_;
        unsigned int minor_;
};

std::ostream& operator<<(std::ostream& os, const unique_id& id);

#endif
