#include "particle.h"

particle::particle(): energy_(NAN), pos_(), dir_(), time_(NAN), length_(NAN), speed_(NAN) {};
    
    // no setter for ID.  just a getter.
unique_id particle::id() const { return id_; }
    
void particle::set_energy(float energy){ energy_ = energy; }
float particle::get_energy() const { return energy_; }
    
void particle::set_position(double x, double y, double z){ pos_ = position(x,y,z); }
position particle::get_position() const { return pos_; }

void particle::set_direction(double zen, double azi){ dir_ = direction(zen,azi); }
direction particle::get_direction() const { return dir_; }

bool particle::operator==(const particle& rhs) const {
  return (energy_ == rhs.get_energy()) && (id_ == rhs.id());
}; // neglect issues with float comparisons
    
bool particle::operator!=(const particle& rhs) const {
  return !(*this == rhs);
}

sim_particle::sim_particle(ParticleShape shape): energy_(NAN), pos_(), dir_(), time_(NAN), length_(NAN), speed_(NAN), shape_(shape) {};

sim_particle::sim_particle(const position pos, const direction dir, ParticleShape shape, ParticleType type=unknown): NOTFINISHEDTHISPART 


class reco_particle: public particle{
  public:

  private:

};


int main(){
  particle p1;
  particle p2;
  
  p1.set_energy(1000);
  p2.set_energy(1000);
 
  p1.set_position(1,2,3);
  cout << p1.get_position() << endl;
  p1.set_direction(0,180);
  cout << p1.get_direction() << endl;

  // p1 and p2 are not the same particle even if their properties are different.
  assert(p1 != p2);
  
  unique_id test_id(p1.id()); // need to be able to copy them and compare later
  
  std::vector<particle> particle_list = {p1, p2};
  
  // i should be able to put them in containers and compare as expected
  assert( test_id == particle_list.front().id() );

  // because some people care about speed, say how fast we are
  {
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i=0;i<1000000;i++) {
      unique_id u;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds diff = end-start;
    std::cout << "Time to make 1 id: "
              << diff.count()/1000000 << " ns\n";
  }
  {
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i=0;i<1000000;i++) {
      particle p;
      p.set_energy(1000);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds diff = end-start;
    std::cout << "Time to make 1 particle with energy: "
              << diff.count()/1000000 << " ns\n";
  }
}
