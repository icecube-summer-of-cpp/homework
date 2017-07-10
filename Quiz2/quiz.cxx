#include <vector>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <iostream>

class unique_id{
  /** A unique identifier.
   *
   * The identifier is specific to this process on this machine,
   * with the start time of the process recorded to be unique across
   * sequential runs.
   *
   * Note that forking is not allowed - handling this increases
   * constructor cost by 5x.
   *
   * Another limiting factor is that only 2^64 ids are available.
   * This could be made larger if there was a need, again for
   * additional constructor cost.
   */
  public:
    unique_id() :
      pid_(global_pid_),
      time_(global_time_),
      cnt_(global_cnt_++)
    { }

    unique_id(const unique_id& rhs) :
        pid_(rhs.pid_),
        time_(rhs.time_),
        cnt_(rhs.cnt_)
    { }

    bool operator==(unique_id rhs) const {
      return (pid_ == rhs.pid_
              && time_ == rhs.time_
              && cnt_ == rhs.cnt_
             );
    }

  private:
    const static uint64_t global_pid_;
    const static uint64_t global_time_;
    static std::atomic<uint64_t> global_cnt_;

    uint64_t pid_;
    uint64_t time_;
    uint64_t cnt_;
};
const uint64_t unique_id::global_pid_ = static_cast<uint64_t>(getpid());
const uint64_t unique_id::global_time_ = std::chrono::system_clock::now().time_since_epoch().count();
std::atomic<uint64_t> unique_id::global_cnt_(0);

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
  
  p1.set_energy(1000);
  p2.set_energy(1000);
  
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
