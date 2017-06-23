//
// Created by Frederik Lauber on 23.06.17.
//

#include <memory>
#include <vector>
#include <assert.h>
#include <cmath>

class unique_id{
    // The class should compare equal to copies of itself,
    // but not to objects created at the same time,
    // on the same machine, in different processes.
    std::shared_ptr<char> _internal_id_object;
    //using a shared_ptr so we do not have to care about freeing our id object
    //also, this reduces all the operators to the default
public:
    ~unique_id() = default;
    unique_id(){_internal_id_object = std::make_shared<char>('1');}
    
    //move assing
    unique_id& operator=(unique_id&& src) = default;
    
    //move construct
    unique_id(unique_id&& v) = default;
    
    //copy constructor
    unique_id(const unique_id& c) = default;
    
    //copy assing
    unique_id& operator=(const unique_id& src) = default;
    
    //use the address in memory of the id object for the comparison
    //as no two objects can be created at the same address,
    //this is a cheap and precise way to do a unique_id
    //as long as we only compare on ONE machine
    bool operator==(const unique_id& rhs) const {
      return this->_internal_id_object.get() ==  rhs._internal_id_object.get();
    };
    
    bool operator!=(const unique_id& rhs) const {
      return this->_internal_id_object.get() !=  rhs._internal_id_object.get();
    }
};

class particle{
public:
    // i should get a unique identifier with the default constructor
    // of unique_id without having to do anything, so no need to include
    // it in the initialization list
    particle(): energy_(NAN) {};//nan i snot defined,
    
    // no setter for ID.  just a getter.
    unique_id id() const { return id_; }
    
    void set_energy(float energy){ energy_ = energy; }
    float get_energy() const { return energy_; } //fixed typo
    
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