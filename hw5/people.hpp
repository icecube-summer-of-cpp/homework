/* Ben Hokanson-Fasig
 * Person class and derived classes
 */

//Include guard
#ifndef __PEOPLE_HEADER_INCLUDED__
#define __PEOPLE_HEADER_INCLUDED__

#include <string>
#include <iostream>


class person
{
    public:
        person() {}
        explicit person(const std::string& name) : name(name) {}
        void set_name(const std::string& n);
        std::string get_name() const;
        void my_name() const;
        virtual void my_infos() const {}
        virtual void all_info() const;

    private:
        std::string name;
};


class student : public virtual person
{
    public:
        student(const std::string& name, const std::string& passed)
            : person(name), passed(passed) {}
        virtual void my_infos() const override;
    
    protected:
        student(const std::string& passed) : passed(passed) {}

    private:
        std::string passed;
};


class mathematician : public virtual person
{
    public:
        mathematician(const std::string& name, const std::string& proved)
            : person(name), proved(proved) {}
        virtual void my_infos() const override;

    protected:
        mathematician(const std::string& proved) : proved(proved) {}
    
    private:
        std::string proved;
};


class math_student : public student, public mathematician
{
    public:
        math_student(const std::string& name, const std::string& passed, const std::string& proved)
            : person(name), student(passed), mathematician(proved) {}
        virtual void my_infos() const override;
        virtual void all_info() const override;
};


#endif
