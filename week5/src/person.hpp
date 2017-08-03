// Summer of C++ 
// Homework Week 5 
// Solution by: Rene Reimann

/*
 * Non-redundant Diamond shape
 * 
 * Implement the Diamond shape from Section 6.3.2 such that the name is only printed once.
 * Distinguish in derived classes between all_info() and my_info() and call the two functions appropriately.
 * 
 *                  PERSON
 *                  +all_info()
 *                  -name
 * 
 *      STUDENT                     MATHEMATICIAN
 *      +all_info()                 +all_info()
 *      -passed                     -proved
 * 
 *                  MATH_STUDENT
 * 
 */

#ifndef PERSON
#define PERSON

#include <iostream>
#include <string>

using namespace std;

class person 
{
  public:
    person() = default;
    explicit person(const string& name) : name(name) {}

    void set_name(const string& n) { name= n; }
    string get_name() const { return name; }
    void my_info() const { cout << "[person]        My name is " << name << endl; }
    virtual void all_info() const { my_info(); }
    
  private:
    string name;
};

class student 
  : public person
{
  public:
    student(const string& name, const string& passed) 
      : person(name), passed(passed) {}
      
    void my_info() const { cout << "[student]       I passed the following grades: " << passed << endl; }  
    virtual void all_info() const override { 
	person::my_info(); 
	my_info();
    }
  private:
    string passed;
};

class mathematician
  : public person
{
  public:
    mathematician(const string& name, const string& proved) 
      : person(name), proved(proved) {}
                                     
    void my_info() const { cout << "[mathematician] I proved: " << proved << endl; }
      
    virtual void all_info() const override { 
	person::my_info(); 
	my_info();
    }
  private:
    string proved;
};

class math_student
  : public student, public mathematician
{
  public:
    math_student(const string& name, const string& passed, const string& proved)
      : student(name, passed), mathematician(name, proved) {}
    virtual void all_info() const override {
	student::all_info();
	mathematician::my_info();
	// person::all_info(); // cannot call member function ‘virtual void person::all_info() const’ without object
    }
};

#endif
