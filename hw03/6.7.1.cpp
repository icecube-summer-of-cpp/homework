#include <iostream>
#include <string>


class person
{
public:
    explicit person(const std::string& name) : name(name) {};
    // Explicit rule of six
    person () = default;
    ~person() = default;
    person(const person& copy_person) = default;
    person(person&& move_person) = default;
    person& operator=(const person& copy_person) = default;
    person& operator=(person& move_person) = default;

    void set_name(const std::string& n) { name = n; }
    std::string get_name() const { return name; };

    virtual void all_info() const {
        std::cout << "[person] My name is " << name << std::endl;
    }

private:
    std::string name;
};


class student : public person
{
public:
    student(const std::string& name, const std::string& passed) :
        person(name), passed(passed) {}

    virtual void all_info() const override {
        std::cout << "[student] My name is " << get_name() << std::endl;
        std::cout << "  I passed the following grades: " << passed << std::endl;
    }

private:
    std::string passed;
};


class mathematician : public person
{
public:
    mathematician(const std::string& name, const std::string& proved) :
        person(name), proved(proved) {};

    virtual void all_info() const override {
        person::all_info();
        std::cout << "  I proved: " << proved << std::endl;
    };

private:
    std::string proved;
};


class math_student : public student, public mathematician
{
public:
    math_student(const std::string& name,
                 const std::string& passed,
                 const std::string& proved) :
                 student(name, passed), mathematician(name, proved) {};

                 virtual void all_info() const override {
                    student::all_info();
                    mathematician::all_info();
                 };
};


int main(int argc, char const *argv[])
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();

    return 0;
}