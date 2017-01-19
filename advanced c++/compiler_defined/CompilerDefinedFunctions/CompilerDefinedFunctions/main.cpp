/*
class Dog {};

// is equivalent to:

class Dog {
public:
	Dog(const Dog& rhs) { ... } // member by member initialization
	Dog& operator=(const Dog& rhs) { ... } // member by member assignment
	Dog() { ... } // 1. Call base class's default constructor
	              // 2. Call each member's default constructor
	~Dog() { ... } // 1. Call base class's destructor
	               // 2. Call each member's destructor
};

About compiler-generated functions:
They are public and inline
They are generated only if needed
They are NOT generated if the compiler is unable to (e.g. if a member is const or reference, if a member's destructor is private etc.)

STL containers require classes with a) copy constructor and b) copy assignment operator
*/

#include <iostream>
#include <string>

using namespace std;

class Collar {
public:
	string m_color;

	Collar(string color) { m_color = color; cout << m_color << " collar is born.\n"; } // the compiler is not able to generate a default constructor
	Collar() : Collar("no color") { }
	//Collar() = default; // C++11
};

class Dog {
	Collar m_collar;
public:
	string m_name;
	// copy constructor: not generated (not needed)
	// copy assignment: generated
	// destructor: not generated (there's one already)
	// default constructor: not generated (a default constructor can have default parameters)
	Dog(string name = "Bob") { m_name = name; cout << name << " is born." << endl; }
	~Dog() { cout << m_name << " is destroyed." << endl; }
};

int main()
{

	{
		Dog dog1("Henry");
		Dog dog2;
		dog2 = dog1; // "Henry is destroyed" appears twice (operator=)
	}
	cin.get();

	return 0;
}