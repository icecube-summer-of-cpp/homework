#include "unique.h"

class unique_id{
   // implementation is left to the user
  public:
    //constructor
    unique_id(...): ... {}
    //default constructor
    unique_id(){}
    //copy constructor
    unique_id(const unique_id& u): ...{}
    //copy assignment
    unique_id& operator=(const unique_id& u_copy) {}
    //move constructor
    unique_id(unique_id&& u): ... {}
    //move assignment
    unique_id& operator=(unique&& u_copy) {}
    //destructor
    ~unique_id(){}

  private:

 };
 
class particle{
public:
    // i should get a unique identifier with the default constructor
    // of unique_id without having to do anything, so no need to include
    // it in the initialization list
    particle(): energy_(NAN) {};
    
    // no setter for ID.  just a getter.
    unique_id id() const { return id_; }
    
    void set_energy(float energy){ energy_ = energy; }
    float get_energy() const { return energy_; } 
    
    bool operator==(const particle& rhs) const {
      return (energy_ == rhs.get_energy()) && (id_ == rhs.id());
    }; // neglect issues with float comparisons
    
    bool operator!=(const particle& rhs) const {
      return !(*this == rhs);
    }

private:
    unique_id id_;
    float energy_;
};

int main(){
  particle p1;
  particle p2;
  
  p1.set_energy(1000); //fixed errors
  p2.set_energy(1000);
  
  // p1 and p2 are not the same particle even if their properties are different.
  assert(p1 != p2);
  
  unique_id test_id(p1.id()); // need to be able to copy them and compare later
  
  std::vector<particle> particle_list = {p1, p2};
  
  // i should be able to put them in containers and compare as expected
  assert( test_id == particle_list.front().id() );
}
