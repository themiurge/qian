#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Dog {
	int age;
	string name;
public:
	Dog() { age = 3; name = "dummy"; }
	void setAge(const int& a) { age = a; cout << "set age const" << endl; } // a cannot be changed
	void setAge(int& a) { age = a; cout << "set age non-const" << endl; } // a cannot be changed

	// const parameters
	//void setAge(const int a) ... // (A) useless, a is a copy anyway
	//void setAge(int a) ... // (B) caller cannot distinguish between (A) and (B) -> compiler error
	//void setAge(const int& a) ... // (C) OK

	// const return value
	const string& getName() { return name; } // return by reference -> improve performance; const -> caller cannot change value
	//const string getName() { return name; } // useless; return value is a copy of name. No performance improvement.

	// const functions
	void printDogName() const { cout << name << " const" << endl; } // this function will not change any of Dog's inner variables
	//void printDogName() const { cout << name << "const" << endl; age++; } // error, cannot change age
	//void printDogName() const { cout << getName() << "const" << endl; } // error, cannot call a non-const function
	void printDogName() { cout << name << " non-const" << endl; } // this function is invoked when the Dog object is NOT a const
};

class BigArray {
	vector<int> v;
	mutable int accessCounter; // mutable variables can be changed in const functions
	int* v2; // another big array
public:
	int getItem(int index) const {
		accessCounter++;
		//const_cast<BigArray*>(this)->accessCounter++; // awful, but works without mutable
		return v[index];
	}

	void setV2Item(int index, int x) const {
		*(v2 + index) = x; // it works because it doesn't change any of the class members directly -> just remove const from function declaration
	}
	
	// quiz: what is this?
	const int*const fun(const int*const& p) const;
	// It's the declaration of a function that accepts a reference to a constant pointer to a const int
	// and returns a constant pointer to a const int, without changing class members.
};

void constKeywordTest();

void constAndFunctions();

void constLogicBitwise();

int main()
{
	constAndFunctions();
	cin.get();
	return 0;
}

void constKeywordTest()
{
	const int i = 9;
	//i = 6; // compiler error
	const_cast<int&>(i) = 6; // OK, cast removes const

	int j = 4;
	//static_cast<const int&>(j) = 7; // compiler error, j is cast as const

	//const int *p1 = &i; // data is const, pointer is not
	//p1++;

	//int* const p2 = 0; // pointer is const, data is not

	//const int * const p3 = 0; // both const

	// if const is on the left of the *, data is const
	// if const is on the right of the *, pointer is const
	int const *p4 = &i; // --> data is const
}

void constAndFunctions()
{
	Dog d;

	int i = 9;
	const int j = 12;
	d.setAge(i); // non-const
	d.setAge(j); // const

	cout << i << endl;

	const string& n = d.getName();
	cout << n << endl;

	d.printDogName(); // non-const

	const Dog d2;
	d2.printDogName(); // const
}

void constLogicBitwise()
{
	BigArray b;

}