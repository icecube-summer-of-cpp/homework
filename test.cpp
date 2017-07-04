#include <iostream>
#include <vector>
#include <random>
#include <assert.h>
#include <unistd.h>  // For using `getpid()`
#include <cmath>


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
        uuid.reserve(uuid_len);

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
    unique_id(const unique_id& copy_id){
        std::cout << "__copy constructored__" << std::endl;
        uuid = copy_id.uuid;
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
    std::vector<int> id() const {
        return this->uuid;
    }

private:
    std::vector<int> uuid;
};


// Outstream << overload
std::ostream& operator<<(std::ostream& os, const unique_id& id){
    std::vector<int> uuid = id.id();
    unsigned long uuid_len = uuid.size();
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
    particle() : energy(NAN) {};

    particle(particle& new_p) : energy(new_p.get_energy()),
                                part_id(new_p.get_id()) {}

    unique_id get_id() {
        return part_id;
    }

    void set_energy(const float en) { energy = en; }
    float get_energy() const { return energy; }

    bool operator==(particle& rhs){
        return part_id == rhs.part_id;
    }

    bool operator!=(particle& rhs){
        return !(part_id == rhs.part_id);
    }

private:
    unique_id part_id;
    float energy;
};


int main(int argc, char const *argv[])
{
    unique_id id1;
    unique_id id2;

    std::cout << "Create id1 and id2, should be different:" << std::endl;
    std::cout << "  id1 is: " << id1 << std::endl;
    std::cout << "  id2 is: " << id2 << std::endl << std::endl;

    std::cout << "Compare id1 to id2: "
              << ((id1 == id2) ? "IDs are same" : "IDs are different")
              << std::endl << std::endl;

    // Test copy constructor
    unique_id test_id(id1);
    std::cout << "Compare id1 to copy of itself: "
              << ((test_id == id1) ? "IDs are same" : "IDs are different")
              << std::endl << std::endl;

    particle p1;
    particle p2;

    p1.set_energy(1000); //fixed errors
    p2.set_energy(1000);

    std::cout << "  P1 id is: " << p1.get_id() << std::endl;
    std::cout << "  P2 id is: " << p2.get_id() << std::endl << std::endl;

    std::cout << "Compare P1 to P2 via ids: "
              << ((p1 == p2) ? "P1 == P2" : "Not P1 == P2")
              << std::endl << std::endl;
    std::cout << "Anti-compare P1 to P2 via ids: "
              << ((p1 != p2) ? "P1 != P2" : "Not P1 != P2")
              << std::endl << std::endl;

    unique_id test_id2(p1.get_id());  // Copy constructored
    std::vector<particle> particle_list = {p1, p2};
    //std::cout << "Put P1 to P2 in vector and compare front to stored id of P1: "
    //          << ((test_id2 == particle_list.front().get_id()) ?
    //              "P1 copied to front" : "P1 not in front")
    //          << std::endl << std::endl;

    return 0;
}
