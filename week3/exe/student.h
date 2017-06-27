#include "person.h"

class student
	: public virtual person
{

	// using person::person;
	public:
		student(const string& name, const string& passed)
			: person(name), passed(passed){}

		virtual void all_info() const {
			person::all_info();
			// cout << "[student] My name is " << name << endl;
			cout << "\tI passes the following grades: " << passed << endl;

		}
	protected:
		student(const string& passed) : passed(passed){}		


	private:
		string passed;



};

class mathematician
	: public virtual person
{
	public:
		mathematician(const string& name, const string& proved)
			: person(name), proved(proved){}

		virtual void all_info() const {
			person::all_info();
			// cout << "[mathman] My name is " << name << endl;
			cout << "\tI proved: " << proved << endl;
		}

	protected:
		mathematician(const string& proved) : proved(proved){}
		virtual void my_info() const{
			cout << "\tI proved: " << proved << endl;	
		}
	private:
		string proved;
};


class math_student
	: public student, public mathematician
{
	public:
		math_student(const string& name, const string& passed, const string& proved)
			:person(name), student(passed), mathematician(proved) {}
			// :student(passed), mathematician(proved) {}

		virtual void all_info() const override{
			student::all_info();
			mathematician::my_info();
		}

};