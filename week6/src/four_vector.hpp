#ifndef FOURVECTOR
#define FOURVECTOR

/*
 * functionallity, tests
 *
 *
 * FOURVECTOR
 * ---------
 * + x1,x2,x3,x4
 * - addition
 * - substraction
 * - scarlar multiplication
 * - dot product
 */

#include <vector>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <cmath>
#include "gtest/gtest.h"

class four_vector {
    public:
        // constructors
        four_vector();
        four_vector(const float x0, const float x1, const float x2, const float x3);
        four_vector(const four_vector&) = default;
        four_vector(four_vector&&) = default;
        four_vector(std::initializer_list<float> values);
        
        // assignment operators
        four_vector& operator=(const four_vector&) = default;
        four_vector& operator=(four_vector&&) = default;
        four_vector& operator=(std::initializer_list<float> values);
        
        // destructor
        ~four_vector() = default;        
        
        // operators
        float operator[](int index) const;
        float& operator[](int index);
        four_vector operator+=(const four_vector& rhs);
        four_vector operator-=(const four_vector& rhs);
        four_vector operator*=(const double scalar);
        
    private:
        std::vector<float> coef_;
    
    // comparison
    friend bool operator==(const four_vector&, const four_vector&);
};

// printing
std::ostream& operator <<(std::ostream&, const four_vector&);

// comparison
bool operator==(const four_vector& lhs, const four_vector& rhs);
bool operator!=(const four_vector& lhs, const four_vector& rhs);
// smaller or greater does not make sens for a four vector

// functionality
four_vector operator+(const four_vector& lhs,  const four_vector& rhs);
four_vector operator-(const four_vector& lhs,  const four_vector& rhs);
four_vector operator*(const double scalar,     const four_vector& vect);
four_vector operator*(const four_vector& vect, const double scalar);
float       operator*(const four_vector& lhs,  const four_vector& rhs);

#endif
