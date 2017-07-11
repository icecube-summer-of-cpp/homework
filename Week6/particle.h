#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <iostream>

#include "position.h"
#include "direction.h"

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
    particle();
    
    // no setter for ID.  just a getter.
    unique_id id() const; 
    
    void set_energy(float energy);
    float get_energy() const;
    
    bool operator==(const particle& rhs) const;
    
    bool operator!=(const particle& rhs) const;

  private:
    unique_id id_;
    float energy_;
    position pos_;
    direction dir_;
    float time_;
    float length_;
    float speed_;
};

//class sim_particle: public particle{
//  public:
//    sim_particle(ParticleShape shape, ParticleType type);
//
//  private:
//    int32_t pdgEncoding_;
//    ParticleShape shape_;
//
//
//};
//
//class reco_particle: public particle{
//  public:
//
//  private:
//
//};

#endif
