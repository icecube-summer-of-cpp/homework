#include "four_vector.hpp"

// constructors
four_vector::four_vector(): coef_{NAN, NAN, NAN, NAN} {};

four_vector::four_vector(const float x0, const float x1, const float x2, const float x3): coef_{x0, x1, x2, x3} {};

four_vector::four_vector(std::initializer_list<float> values): coef_(values){ 
    assert( values.size() == 4 ); 
};

// assignments
four_vector& four_vector::operator=(std::initializer_list<float> values){
    assert( values.size() == coef_.size() );
    std::copy(std::begin(values), std::end(values), std::begin(coef_));
    return *this;
};

// operators
float four_vector::operator[](int index) const {
    assert( index < coef_.size() ); 
    return coef_[index];
}
 
float& four_vector::operator[](int index) { 
    assert(index < coef_.size());
    return coef_[index];
}

four_vector four_vector::operator+=(const four_vector& rhs){
    for(int index=0; index<4; index++){
        coef_[index] = coef_[index] + rhs[index];
    }
    return *this;
};

four_vector four_vector::operator-=(const four_vector& rhs){
    for(int index=0; index<4; index++){
        coef_[index] = coef_[index] - rhs[index];
    }
    return *this;
};

four_vector four_vector::operator*=(const double scalar){
    for(int index=0; index<4; index++){
        coef_[index] = coef_[index] * scalar;
    }
    return *this;
};

// printing
std::ostream& operator <<(std::ostream& os, const four_vector& vect){
    std::stringstream s("");
    s << "(";
    for (int i = 0; i < 4; i++){
        s << vect[i] << ((i < 3) ? ", "  : "") ; 
    }
    s << ")";
    return os << s.str() ;
}

// comparison
bool operator==(const four_vector& lhs, const four_vector& rhs) { 
    return (lhs.coef_ == rhs.coef_); 
};

bool operator!=(const four_vector& lhs, const four_vector& rhs) {
    return !(lhs == rhs);
};

// functionality
four_vector operator+(const four_vector& lhs, const four_vector& rhs){
    four_vector temp;
    for(int index=0; index<4; index++){
        temp[index] = lhs[index] + rhs[index];
    }
    return temp;
};

four_vector operator-(const four_vector& lhs, const four_vector& rhs){
    return lhs + (-1.*rhs);
}

four_vector operator*(const four_vector& vect, const double scalar){
    four_vector temp;
    for(int index=0; index<4; index++){
        temp[index] = vect[index] * scalar;
    }
    return temp;
}

four_vector operator*(const double scalar, const four_vector& vect){
    return vect*scalar;
};

float       operator*(const four_vector& lhs, const four_vector& rhs){
    float sum = lhs[0] * rhs[0];
    for(int index=1; index<4; index++){
        sum -= lhs[index] * rhs[index];
    }
    return sum;
}
