#include "particle.hpp"

// constructor
particle::particle(): properties_(particle_type::unknown) {};
particle::particle(particle_type p_type): properties_(p_type) {};
particle::particle(particle_type p_type, four_vector ct_x, four_vector e_p): properties_(p_type), time_space_(ct_x), energy_momentum_(e_p) {};

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

void particle::set_energy_momentum(four_vector v){ 
    double v2 = v[0]*v[0] - (v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
    double m2 = properties_.mass()*properties_.mass();
    assert(m2 == v2);
    energy_momentum_ = v;
};
four_vector particle::get_energy_momentum() const {return energy_momentum_;};
        
void particle::set_spacetime_point(four_vector v) {
    double v2 = v[0]*v[0] - (v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
    if (get_mass() != 0){ assert(v2 > 0); }
    else {assert(v2 == 0); }
    time_space_ = v;
};
four_vector particle::get_spacetime_point() const {return time_space_; };
        
//particle_type particle::get_particle() const { return properties_.type(); };
        
double particle::get_mass() const {return properties_.mass();};
int particle::get_charge() const {return properties_.charge();};
float particle::get_spin() const {return properties_.spin();};

float particle::get_zenith() const {return 1.;}; // ToDo
float particle::get_azimuth() const {return 1.;}; // ToDo

// print 
std::ostream& operator <<(std::ostream& os, const particle& p){
    return os << "type: " << p.properties_ << " Time/Space: " << p.time_space_ 
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

TEST(ParticleTest, simparticle) {
    sim_particle a;
    a.set_shape(sim_particle::shape::cascade);
    std::cout << a << std::endl;
}

TEST(ParticleTest, recoparticle) {
    reco_particle a;
    a.set_shape(reco_particle::shape::cascade);
    a.set_status(reco_particle::status::good);
    std::cout << a << std::endl;
    
}
