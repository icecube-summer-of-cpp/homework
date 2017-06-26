#include <iostream>
#include <vector>
#include <random>
#include <assert.h>
#include <unistd.h>  // For using `getpid()`
#include <cmath>
#include <ctime>


class unique_id {
public:
    // Rule of Six: create all or none of:
    // Constr., Destr., CopyConstr., MoveConstr., MoveAssign., CopyAssign.
    // Standard constructor
    unique_id(){
        std::cout << "__standard constructored__" << std::endl;
        // Construct UUID using N random ints in [0, 9],  seeded with rnd + pid
        // Don't know if that is OK...
        const int uuid_len = 48;
        uuid.resize(uuid_len);

        // Setup the rnd gen
        const int pid = getpid();
        std::random_device rd;
        std::mt19937 mt_gen(rd() + pid);
        std::uniform_int_distribution<> rand_int(0, 9);

        // Fill with random ints
        for (int i = 0; i < uuid_len; ++i) {
            uuid[i] = rand_int(mt_gen);
        }
    };

    // Set destructor to default
    ~unique_id() = default;

    // Copy Constructor
    unique_id(unique_id& copy_id){
        std::cout << "__copy constructored__" << std::endl;
        uuid = copy_id.id();
    }

    // Move constructor -> How to do without setter?
    unique_id(unique_id&& move_id){
        std::cout << "__move constructored (wrongly)__" << std::endl;
        uuid = move_id.id();
        // This is not correct, equivalent to copy...
        // How to let the move_id vanish?
    }

    // Copy assignment
    unique_id& operator=(unique_id& copy_id){
        std::cout << "__copy assignored__" << std::endl;
        uuid = copy_id.id();
        return *this;
    }

    // Move assignment
    unique_id& operator=(unique_id&& move_id){
        // Same as in move constructor
        std::cout << "__move assignored__" << std::endl;
        uuid = move_id.id();
        return *this;
    }

    // Comparator == overload
    bool operator==(unique_id& other_id){
        return (uuid == other_id.id());
    }

    // Getter, no setter
    std::vector<int>& id(){
        return uuid;
    }

private:
    std::vector<int> uuid;
};


// Outstream << overload
std::ostream& operator<<(std::ostream& os, unique_id& id){
    std::vector<int> uuid = id.id();
    int uuid_len = uuid.size();
    for (int i = 0; i < uuid_len; ++i) {
        os << uuid[i];
        if (((i + 1) % 4 == 0) && (i < uuid_len - 1)) {
            os << "-";
        }
    }
    return os;
}


class particle {
public:
    // I should get a unique identifier with the default constructor
    // of unique_id without having to do anything, so no need to include
    // it in the initialization list
    particle(): energy_(NAN) {};

    // No setter for ID, just a getter.
    unique_id id() const { return id_; }

    void set_energy(float energy){ energy_ = energy; }
    float get_energy() const { return energy_; } //fixed typo

    bool operator==(const particle& rhs) const {
      return (energy_ == rhs.get_energy()) && (id_ == rhs.id());
    }; // Neglect issues with float comparisons

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

  // // p1 and p2 are not the same particle even if their properties are identical.
  // assert(p1 != p2);

  // unique_id test_id(p1.id()); // need to be able to copy them and compare later

  // std::vector<particle> particle_list = {p1, p2};

  // // i should be able to put them in containers and compare as expected
  // assert( test_id == particle_list.front().id() );
}
