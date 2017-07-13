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

//****************************//
//         Base class         //
//****************************//
class particle{
  public:
    enum ParticleType { // NB: These match the PDG codes. Keep it that way!
    unknown = 0,
    Gamma = 22,
    EPlus = -11,
    EMinus = 11,
    MuPlus = -13,
    MuMinus = 13,
    Pi0 = 111,
    PiPlus = 211,
    PiMinus = -211,
    K0_Long = 130,
    KPlus = 321,
    KMinus = -321,
    Neutron = 2112,
    PPlus = 2212,
    PMinus = -2212,
    K0_Short = 310,
    Eta = 221,
    Lambda = 3122,
    SigmaPlus = 3222,
    Sigma0 = 3212,
    SigmaMinus = 3112,
    Xi0 = 3322,
    XiMinus = 3312,
    OmegaMinus = 3334,
    NeutronBar = -2112,
    LambdaBar = -3122,
    SigmaMinusBar = -3222,
    Sigma0Bar = -3212,
    SigmaPlusBar = -3112,
    Xi0Bar = -3322,
    XiPlusBar = -3312,
    OmegaPlusBar = -3334,
    DPlus = 411,
    DMinus = -411,
    D0 = 421,
    D0Bar = -421,
    DsPlus = 431,
    DsMinusBar = -431,
    LambdacPlus = 4122,
    WPlus = 24,
    WMinus = -24,
    Z0 = 23,
    NuE = 12,
    NuEBar = -12,
    NuMu = 14,
    NuMuBar = -14,
    TauPlus = -15,
    TauMinus = 15,
    NuTau = 16,
    NuTauBar = -16,
    
    /* Nuclei */
    He3Nucleus = 1000020030,
    He4Nucleus = 1000020040,
    Li6Nucleus = 1000030060,
    Li7Nucleus = 1000030070,
    Be9Nucleus = 1000040090,
    B10Nucleus = 1000050100,
    B11Nucleus = 1000050110,
    C12Nucleus = 1000060120,
    C13Nucleus = 1000060130,
    N14Nucleus = 1000070140,
    N15Nucleus = 1000070150,
    O16Nucleus = 1000080160,
    O17Nucleus = 1000080170,
    O18Nucleus = 1000080180,
    F19Nucleus = 1000090190,
    Ne20Nucleus = 1000100200,
    Ne21Nucleus = 1000100210,
    Ne22Nucleus = 1000100220,
    Na23Nucleus = 1000110230,
    Mg24Nucleus = 1000120240,
    Mg25Nucleus = 1000120250,
    Mg26Nucleus = 1000120260,
    Al26Nucleus = 1000130260,
    Al27Nucleus = 1000130270,
    Si28Nucleus = 1000140280,
    Si29Nucleus = 1000140290,
    Si30Nucleus = 1000140300,
    Si31Nucleus = 1000140310,
    Si32Nucleus = 1000140320,
    P31Nucleus = 1000150310,
    P32Nucleus = 1000150320,
    P33Nucleus = 1000150330,
    S32Nucleus = 1000160320,
    S33Nucleus = 1000160330,
    S34Nucleus = 1000160340,
    S35Nucleus = 1000160350,
    S36Nucleus = 1000160360,
    Cl35Nucleus = 1000170350,
    Cl36Nucleus = 1000170360,
    Cl37Nucleus = 1000170370,
    Ar36Nucleus = 1000180360,
    Ar37Nucleus = 1000180370,
    Ar38Nucleus = 1000180380,
    Ar39Nucleus = 1000180390,
    Ar40Nucleus = 1000180400,
    Ar41Nucleus = 1000180410,
    Ar42Nucleus = 1000180420,
    K39Nucleus = 1000190390,
    K40Nucleus = 1000190400,
    K41Nucleus = 1000190410,
    Ca40Nucleus = 1000200400,
    Ca41Nucleus = 1000200410,
    Ca42Nucleus = 1000200420,
    Ca43Nucleus = 1000200430,
    Ca44Nucleus = 1000200440,
    Ca45Nucleus = 1000200450,
    Ca46Nucleus = 1000200460,
    Ca47Nucleus = 1000200470,
    Ca48Nucleus = 1000200480,
    Sc44Nucleus = 1000210440,
    Sc45Nucleus = 1000210450,
    Sc46Nucleus = 1000210460,
    Sc47Nucleus = 1000210470,
    Sc48Nucleus = 1000210480,
    Ti44Nucleus = 1000220440,
    Ti45Nucleus = 1000220450,
    Ti46Nucleus = 1000220460,
    Ti47Nucleus = 1000220470,
    Ti48Nucleus = 1000220480,
    Ti49Nucleus = 1000220490,
    Ti50Nucleus = 1000220500,
    V48Nucleus = 1000230480,
    V49Nucleus = 1000230490,
    V50Nucleus = 1000230500,
    V51Nucleus = 1000230510,
    Cr50Nucleus = 1000240500,
    Cr51Nucleus = 1000240510,
    Cr52Nucleus = 1000240520,
    Cr53Nucleus = 1000240530,
    Cr54Nucleus = 1000240540,
    Mn52Nucleus = 1000250520,
    Mn53Nucleus = 1000250530,
    Mn54Nucleus = 1000250540,
    Mn55Nucleus = 1000250550,
    Fe54Nucleus = 1000260540,
    Fe55Nucleus = 1000260550,
    Fe56Nucleus = 1000260560,
    Fe57Nucleus = 1000260570,
    Fe58Nucleus = 1000260580,

    /* The following are fake particles used in Icetray and have no official codes */
    /* The section abs(code) > 2000000000 is reserved for this kind of use */
    CherenkovPhoton = 2000009900,
    Nu = -2000000004,
    Monopole = -2000000041,
    Brems = -2000001001,
    DeltaE = -2000001002,
    PairProd = -2000001003,
    NuclInt = -2000001004,
    MuPair = -2000001005,
    Hadrons = -2000001006,
    ContinuousEnergyLoss = -2000001111,
    FiberLaser = -2000002100,
    N2Laser = -2000002101,
    YAGLaser = -2000002201,
    STauPlus = -2000009131,
    STauMinus = -2000009132,
    SMPPlus = -2000009500,
    SMPMinus = -2000009501,
  };

    // i should get a unique identifier with the default constructor
    // of unique_id without having to do anything, so no need to include
    // it in the initialization list
    particle();

    particle(const position pos, const direction dir, ParticleType type = unknown);
    
    // no setter for ID.  just a getter.
    unique_id id() const; 
    
    void set_energy(float energy);
    float get_energy() const;
    void set_position(double x,double y, double z);
    position get_position() const;
    void set_direction(double zen, double azi);
    direction get_direction() const;

    bool operator==(const particle& rhs) const;
    
    bool operator!=(const particle& rhs) const;

  private:
    int32_t pdgEncoding_;
    unique_id id_;
    float energy_;
    position pos_;
    direction dir_;
    float time_;
    float length_;
    float speed_;
};

//****************************//
//          sim class         //
//****************************//
class sim_particle: public particle{
  public:
    enum ParticleShape { 
    Primary = 10, 
    TopShower = 20, 
    Cascade = 30, 
    CascadeSegment = 31, 
    InfiniteTrack = 40, 
    StartingTrack = 50, 
    StoppingTrack = 60, 
    ContainedTrack = 70,
    MCTrack = 80,
    Dark = 90
  };
    sim_particle(ParticleShape shape);
    sim_particle(const float energy, const position pos, const direction dir, const float time, const float length, const float speed, ParticleShape shape, ParticleType type=unknown);

  private:
    ParticleShape shape_;

};

//****************************//
//         Reco class         //
//****************************//
class reco_particle: public particle{
  public:
    enum FitStatus {
    OK = 0,
    GeneralFailure = 10,
    InsufficientHits = 20,
    FailedToConverge = 30,
    MissingSeed = 40,
    InsufficientQuality = 50
  };
    reco_particle(FitStatus status);
    reco_particle(const float energy, const position pos, const direction dir, const float time, const float length, const float speed, FitStatus status, ParticleType type=unknown);

  private:
    FitStatus status_;

};


#endif
