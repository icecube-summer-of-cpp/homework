#include "particle.hpp"

// constructor
particle::particle(): quantum_numb_(particle_type::undefined) {};
particle::particle(particle_type p_type): quantum_numb_(p_type) {};
particle::particle(particle_type p_type, four_vector ct_x, four_vector e_p): quantum_numb_(p_type), time_space_(ct_x), energy_momentum_(e_p) {};

// comparisons
bool particle::operator==(const particle& rhs) const { 
    return (id_ == rhs.id()); // (energy_ == rhs.get_energy()) && 
}; 

bool particle::operator!=(const particle& rhs) const { 
    return !(*this == rhs); 
};

// getters and setters
unique_id particle::id() const { 
    return id_; 
};

void particle::set_energy(float energy){ 
    energy_momentum_[0] = energy; 
};

float particle::get_energy() const { 
    return energy_momentum_[0]; 
};

// print 
std::ostream& operator <<(std::ostream& os, const particle& p){
    return os << "type: " << name(p.quantum_numb_) << " Time/Space: " << p.time_space_ 
              << " Energy/Momentum: " << p.energy_momentum_ 
              << " identifier: " << p.id_;
}
 
// tests

TEST(ParticleTest, constructor) {
    particle a;
    particle b(a);
    particle c(particle_type::muon);
    particle d(particle_type::muon, four_vector(0, 1, 2, 3), four_vector(1, 2, 3, 4));
    EXPECT_EQ(a, b);
    std::cout << a << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
}
