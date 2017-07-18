#include "particle.hpp"

// test particle

// constructor

// print 
std::ostream& operator <<(std::ostream& os, const particle& p){
    return os << "type: " << charge(p.quantum_numb_) << " Time/Space: " << p.time_space_ 
              << " Energy/Momentum: " << p.energy_momentum_ 
              << " identifier: " << p.id_;
}
 
// tests

TEST(ParticleTest, constructor) {
    particle a;
    particle b(a);
    particle c(particle_type::muon);
    EXPECT_EQ(a, b);
    std::cout << a << std::endl;
    std::cout << c << std::endl;
}
