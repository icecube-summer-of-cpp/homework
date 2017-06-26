#include <iostream>
#include <vector>
#include <random>
#include <assert.h>
#include <unistd.h>  // For using `getpid()`
#include <cmath>
#include <ctime>


class unique_id{
public:
    unique_id() {
        std::random_device rnd;
        std::mt19937 mt_gen(rnd() + getpid());
        std::uniform_int_distribution<> rand_int(0, 9);

        for (int i = 0; i < uuid_len; ++i)
        {
            uuid.push_back(rand_int(mt_gen));
        }
    }

    unique_id(const unique_id& copy_id) {
        for (int i = 0; i < uuid_len; ++i) { uuid.push_back(copy_id.id()[i]); }
    }

    unique_id& operator=(const unique_id& copy_id) {
        for (int i = 0; i < uuid_len; ++i) { uuid.push_back(copy_id.id()[i]); }
        return *this;
    }

    ~unique_id() = default;
    unique_id(unique_id&& move_id) = delete;
    unique_id& operator=(const unique_id&& move_id) = delete;

    const std::vector<unsigned>& id() const { return uuid; }

    bool operator==(const unique_id& other_id) const {
        return (uuid == other_id.id());
    }

private:
    std::vector<unsigned> uuid;
    const unsigned uuid_len = 48;
};

// Outstream << overload
std::ostream& operator<<(std::ostream& os, const unique_id& id){
    std::vector<unsigned> uuid = id.id();
    int uuid_len = uuid.size();
    for (int i = 0; i < uuid_len; ++i) {
        os << uuid[i];
        if (((i + 1) % 4 == 0) && (i < uuid_len - 1)) {
            os << "-";
        }
    }
    return os;
}


class particle{
public:
    particle(): energy_(NAN) {};
    ~particle() = default;

    const unique_id& id() const { return id_; }

    void set_energy(float energy){ energy_ = energy; }
    float get_energy() const { return energy_; }

    bool operator==(const particle& rhs) const {
      return (energy_ == rhs.get_energy()) && (id_ == rhs.id());
    };

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

    // p1 and p2 are not the same particle even if their properties are identical.
    assert(p1 != p2);

    unique_id test_id(p1.id()); // need to be able to copy them and compare later

    std::vector<particle> particle_list = {p1, p2};

    // i should be able to put them in containers and compare as expected
    assert( test_id == particle_list.front().id() );


    unique_id id1;
    unique_id id2;

    std::cout << "Create id1 and id2, should be different:" << std::endl;
    std::cout << "  id1 is: " << id1 << std::endl;
    std::cout << "  id2 is: " << id2 << std::endl << std::endl;

    std::cout << "Compare id1 to id2, should still be different: "
            << ((id1 == id2) ? "IDs are same" : "IDs are different")
            << std::endl << std::endl;

    // Test copy constructor
    unique_id copy_id1(id1);
    std::cout << "Compare id1 to copy of itself: "
              << ((copy_id1 == id1) ? "IDs are same" : "IDs are different")
              << std::endl << std::endl;

    std::cout << "Show particle IDs, should be different:" << std::endl;
    std::cout << "  P1 id is: " << p1.id() << std::endl;
    std::cout << "  P2 id is: " << p2.id() << std::endl << std::endl;

    std::cout << "Compare P1 to P2 directly via ids, should be different: "
              << ((p1 == p2) ? "Particles differ" : "Particles are the same")
              << std::endl << std::endl;

    std::cout << "Anti-Compare P1 to P2 directly via ids, should be different: "
              << ((p1 != p2) ? "p1 != p2 is True" : "p1 != p2 is False")
              << std::endl << std::endl;

    unique_id test_id2(p1.id());
    std::cout << "Put P1 to P2 in vector and compare front to stored id of P1: "
              << ((test_id2 == particle_list.front().id()) ?
                  "P1 copied to front" : "P1 not in front")
              << std::endl << std::endl;
}
