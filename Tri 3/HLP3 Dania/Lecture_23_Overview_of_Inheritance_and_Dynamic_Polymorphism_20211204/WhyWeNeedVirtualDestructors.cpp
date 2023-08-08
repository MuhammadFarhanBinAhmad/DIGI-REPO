/*******************************************************************************
 * This example shows:
 *
 * - Why we need virtual destructors is a class is operated on by a base class
 *   pointer/reference (calling a delete expression on a base class pointer
 *   calls an incorrect destructor).
 *
 * - The syntax of pure virtual functions. Such member functions cannot be
 *   defined in a class definition, require an override in a derived class, and
 *   make the a class "abstract". Abstract classes cannot be instantiated, but
 *   can be inherited, and we can use pointers to such classes.
 ******************************************************************************/

#include <iostream>
#include <string>

class Base {
public:
	Base() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	// This is a pure virtual function.
	virtual void print() const = 0;

	// Should be virtual, but a programmer forgot about it...
	~Base() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

class Derived : public Base {
public:
	Derived() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	// Overrides a member function that is pure in a base class; therefore, this
	// class is no longer abstract and can be instantiated.
	virtual void print() const override {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual ~Derived() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

int main() {
	{
		std::cout << "Own class pointer; this should work fine...\n";

		Derived *derived = new Derived;
		derived->print();
		delete derived;
	}

	std::cout << "\n";

	{
		std::cout << "Base class pointer; this causes a memory leak...\n";

		Base *base = new Derived;
		base->print();
		// Compile without -Werror flag as g++ may warn you about this issue...
		delete base;
	}

	/*{
		std::cout
			<< "Construction of an abstract class; "
			<< "this does not even compile." << std::endl;

		Base* base = new Base;
		base->print();
		delete base;
	}*/
}
