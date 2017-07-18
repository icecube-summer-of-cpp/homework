// Summer of C++ 
// Homework Week 6 
// Solution by: Rene Reimann

/*
 * 
 * Write a particle base class and a sim_particle and reco_particle derived classes. 
 * Along the way you'll probably want to implement direction and position classes. 
 * The unique_id class will likely come in handy as well.
 * 
 */

#include <iostream>
#include <sstream>
#include "unique_id.hpp"
#include "particle.hpp"
#include "four_vector.hpp"
#include <vector>
#include <cassert>
#include "gtest/gtest.h"

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
    a -= b;
    c = a;
    EXPECT_EQ(a, -1*b);
    b += a;
    EXPECT_EQ(a, c);
    c = b + b;
    EXPECT_EQ(c, 2*b);
    c = b - b;
    EXPECT_EQ(c, a);
}

TEST(FourVectorTest, ScalarMultiplication) {
}

TEST(FourVectorTest, ScalarProd) {
  four_vector x{0,1,2,3};
  EXPECT_FALSE(x*x >0);
  EXPECT_TRUE(x*x == -14);
}

int main (int argc, char **argv) 
{
    
    std::cout << "Test-Four Vector" << std::endl;
    
    four_vector x;
    four_vector y{0, 1, 2, 3};
    four_vector z = {0, 2, 4, 6};
    std::cout << z << std::endl;
    
    x = y + z;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    x += y;
    
    std::cout << x << std::endl;
    
    x *= 2;
    
    std::cout << x << std::endl;
    
    std::cout << 2*x << std::endl;
    
    std::cout << 2*x - y << std::endl;
    
    std::cout << x*x << std::endl;
    
    x = z;
    std::cout << x << std::endl;
    
    y = {5,4,3,2};
    std::cout << y << std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    //z = {0, 1, 2};
    //std::cout << z << std::endl;
    
    /*
    particle p1;
    particle p2;
   
    p1.set_energy(1000);
    p2.set_energy(1000);
   
    // p1 and p2 are not the same particle even if their properties are different.
    assert(p1 != p2);
   
    unique_id test_id(p1.id()); // need to be able to copy them and compare later
   
    std::vector<particle> particle_list = {p1, p2};
   
    // i should be able to put them in containers and compare as expected
    assert( test_id == particle_list.front().id() );
    */
    return 0 ;
}
