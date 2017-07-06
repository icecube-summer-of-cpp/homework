#include <iostream>
#include <string>

class person
{
public:
    explicit person(const std::string& name) : name(name) {};
    person () = default;
    // Not need for the example but good practice I guess
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

class student : public virtual person
{
public:
    student(const std::string& name, const std::string& passed) :  person(name), passed(passed) {};

    virtual void all_info() const override {
        person::all_info();
        my_info();
    };

protected:
    student(const std::string& passed) : passed(passed) {};

    virtual void my_info() const {
        std::cout << " I passed the following grades: " << passed << std::endl;
    };

private:
    std::string passed;
};


class mathematician : public virtual person
{
public:
    mathematician(const std::string& name, const std::string& proved) : person(name), proved(proved) {};

    virtual void all_info() const override {
        person::all_info();
        my_info();
    };

protected:
    mathematician(const std::string& proved) : proved(proved) {};

    virtual void my_info() const {
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
                 person(name), student(passed), mathematician(proved) {};

     virtual void all_info() const override {
        student::all_info();
        mathematician::my_info();
     };
};


int main(int argc, char const *argv[])
{
    math_student horst("Horst Horstson", "Nothing", "to be a failure");
    horst.all_info();

    return 0;
}
