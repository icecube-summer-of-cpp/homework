/**
 * Solution to exercise 6.7.1
 */

#include <iostream>
#include <string>

class person
{
    public:
        person(const std::string& name) : name(name) {}

        person() = default;
        person(const person&) = default;
        person(person&&) = default;

        virtual ~person() = default;

        person& operator=(const person&) = default;
        person& operator=(person&&) = default;

        virtual void all_info() const
        {
            std::cout << "My name is " << name << "." << std::endl;
        }

    private:
        std::string name;
};

class student : public virtual person
{
    public:
        student(const std::string& name, const std::string& passed)
            : person(name), passed(passed) {}

        student() = default;
        student(const student&) = default;
        student(student&&) = default;

        virtual ~student() = default;

        student& operator=(const student&) = default;
        student& operator=(student&&) = default;

        virtual void all_info() const override
        {
            person::all_info();
            my_infos();
        }

    protected:
        student(const std::string& passed) : passed(passed) {}

        virtual void my_infos() const
        {
            std::cout << "I passed the following grades: "
                      << passed << "." << std::endl;
        }

    private:
        std::string passed;
};

class mathematician : public virtual person
{
    public:
        mathematician(const std::string& name, const std::string& proved)
            : person(name), proved(proved) {}

        mathematician() = default;
        mathematician(const mathematician&) = default;
        mathematician(mathematician&&) = default;

        virtual ~mathematician() = default;

        mathematician& operator=(const mathematician&) = default;
        mathematician& operator=(mathematician&&) = default;

        virtual void all_info() const override
        {
            person::all_info();
            my_infos();
        }

    protected:
        mathematician(const std::string& proved) : proved(proved) {}

        void my_infos() const
        {
            std::cout << "I proved: " << proved << "." << std::endl;
        }

    private:
        std::string proved;
};

class math_student : public student, public mathematician
{
    public:
        math_student(const std::string& name, const std::string& passed,
                     const std::string& proved)
            : person(name), student(passed), mathematician(proved) {}

        math_student() = default;
        math_student(const math_student&) = default;
        math_student(math_student&&) = default;

        ~math_student() final = default;

        math_student& operator=(const math_student&) = default;
        math_student& operator=(math_student&&) = default;

        void all_info() const final
        {
            student::all_info();
            mathematician::my_infos();
        }
};


int main()
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();
}
