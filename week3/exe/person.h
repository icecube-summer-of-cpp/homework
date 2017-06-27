#include <iostream>
#include <string>

using namespace std;

class creature{
	virtual void all_info() const = 0; // pure virtual
};

class person
	: public creature
{

	public:	
		person() {}
		explicit person(const string& name) : name(name){}

		void set_name(const string& n){name = n;}
		string get_name() const {return name;}
		virtual void all_info() const {
			cout << "[person] My name is " << name << endl;

		}

	private:
		string name;

};