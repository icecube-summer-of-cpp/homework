#include <iostream>
#include <string>


class person
{
public:
    explicit person(const std::string& new_name) : name(new_name) {};
    ~person() = default;
    person(const person& copy_person) = delete;
    person(person&& move_person) = delete;
    person& operator=(const person& copy_person) = delete;
    person& operator=(person& move_person) = delete;

    void set_name(const std::string& new_name) { name = new_name; }
    std::string get_name() { return name; };

    void all_info() const {
        std::cout << "[person] My name is " << name << std::endl;
    }

private:
    std::string name;
};



int main(int argc, char const *argv[])
{

    return 0;
}