#include <iostream>
#include <string>

using namespace std;

class person
{
    string name;
public:
    person() = default;
    explicit person(const string& name) : name(name) {}
    
    void set_name(const string& n) { name= n; }
    string get_name() const { return name; }
    virtual void all_info() const {
      cout << "[person] ";
      person::my_info();
    }
    virtual void my_info() const {
      cout << "    My name is : " << name << endl;
    }
};

class student : public virtual person {
    string passed;
public:
    student(const string& name, const string& passed)
            : person(name), passed(passed) {}
    virtual void all_info() const override {
      cout << "[student] ";
      person::my_info();
      my_info();
    }
    
    virtual void my_info() const {
      cout << "    I passed the following grades: " << passed << endl;
    }

};

class mathematician : public virtual person {
    string proved;
public:
    mathematician(const string& name, const string& proved)
            : person(name), proved(proved) {}
    virtual void all_info() const override {
      cout << "[mathman] ";
      person::my_info();
      my_info();
    }
    
    virtual void my_info() const {
      cout << "    I proved: " << proved << endl;
    }
};

class math_student : public student, public mathematician {
public:
    math_student(const string& name, const string& passed, const string& proved)
            : person(name), student(name, passed), mathematician(name, proved) {}
    virtual void all_info() const override {
      my_info();
      person::my_info();
      student::my_info();
      mathematician::my_info();
    }
    
    virtual void my_info() const {
      cout << "[mathstud]";
    };
};

int main ()
{
  math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
  bob.all_info();
  return 0 ;
}