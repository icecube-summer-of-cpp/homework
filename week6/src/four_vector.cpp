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

TEST(FourVectorTest, Constructors) {
  four_vector a;
  four_vector b{0,1,2,3};
  four_vector c = {0,1,2,3};
  four_vector d(b);
  four_vector e(0, 1, 2, 3);
  EXPECT_NE(a, a);
  EXPECT_EQ(b, b);
  EXPECT_EQ(c, c);
  EXPECT_EQ(d, d);
  EXPECT_EQ(e, e);
  EXPECT_NE(a, b);
  EXPECT_EQ(c, b);
  EXPECT_EQ(d, b);
  EXPECT_EQ(e, b);
}

TEST(FourVectorTest, AssignmentsGetterSetter) {
  four_vector a;
  four_vector b{0,1,2,3};
  four_vector c;
  c = b;
  a[0] = 0;
  a[1] = 1;
  a[2] = 2;
  a[3] = 3;
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, b);
  EXPECT_EQ(c, b);
  EXPECT_EQ(b[0], 0.);
  EXPECT_EQ(b[1], 1.);
  EXPECT_EQ(b[2], 2.);
  EXPECT_EQ(b[3], 3.);
}

TEST(FourVectorTest, Printing) {
    std::string a = "(0, 1, 2, 3)";
    four_vector b{0,1,2,3};
    std::stringstream stream("");
    stream << b;
    EXPECT_EQ(a, stream.str());
}

TEST(FourVectorTest, Addition) {
    four_vector a= {0, 0, 0, 0};
    four_vector b= {0, 1, 2, 3};
    four_vector c;
    four_vector d= {0, 2, 4, 6};
    a += {0, 1, 2, 3};
    EXPECT_EQ(a, b);
    c = b + b;
    EXPECT_EQ(c, d);
}

TEST(FourVectorTest, Substraction) {
    four_vector a= {0, 0, 0, 0};
    four_vector b= {0, 1, 2, 3};
    four_vector c;
    four_vector d= {0, 2, 4, 6};
    c = a;
    a -= b;
    EXPECT_EQ(a, -1*b);
    a += b;
    EXPECT_EQ(a, c);
    c = b + b;
    EXPECT_EQ(c, 2*b);
    c = b - b;
    EXPECT_EQ(c, a);
}

TEST(FourVectorTest, ScalarMultiplication) {
    four_vector a= {0, 0, 0, 0};
    four_vector b= {0, 1, 2, 3};
    four_vector c = b;
    
    c *= -1;

    EXPECT_EQ(a-b, c);
    EXPECT_EQ(b+b+b, 3*b);
    EXPECT_EQ(a, 0*b);
}

TEST(FourVectorTest, ScalarProd) {
  four_vector x{0,1,2,3};
  EXPECT_FALSE(x*x >0);
  EXPECT_TRUE(x*x == -14);
}
