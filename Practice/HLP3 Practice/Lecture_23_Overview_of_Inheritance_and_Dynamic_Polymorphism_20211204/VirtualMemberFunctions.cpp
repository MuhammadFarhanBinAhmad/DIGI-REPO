/*******************************************************************************
 * This example shows a difference between non-virtual and virtual member
 * function calls.
 *
 * A non-virtual member function is always called from a scope of the "this"
 * object's current type (a current type of a pointer). A virtual member
 * function can be called from a scope of the "this" object's real type (a type
 * from its construction). This technique of run-time polymorphism lets
 * programmers introduce behaviour in derived objects that overrides the one
 * inherited from their base classes.
 *
 * Virtual function calls only work for pointers and references! They have
 * a minor performance cost, but allow for invoking derived functions through
 * base class pointers or references.
 ******************************************************************************/

#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

class Weapon {
private:
	int const damage;
protected:
	int const weight;
public:
	Weapon(int d) : damage{d}, weight{10} {}

	// Non-virtual member function.
	int Damage() const {
		return damage;
	}

	// Virtual member function.
	virtual void print() const {
		std::cout << "This weapon weights " << weight << "kg.\n";
	}

	// If a class has anything virtual, mark its destructor as virtual.
	virtual ~Weapon() = default;
};

////////////////////////////////////////////////////////////////////////////////

class Sword : public Weapon {
	std::string name;
public:
	Sword() : Weapon{100}, name{"Excalibur"} {}

	std::string Name() const { return name; }

	// Virtual member function overriding a function with the same signature
	// from a base class. Keyword "virtual" can be omitted as virtual-ness
	// is hereditary. Keyword "override" is optional and lets the compiler break
	// compilation if a base class does not have a member function to be
	// overriden by this function (prevents accidental mistakes with different
	// parameters or function renaming).
	virtual void print() const override {
		// weight is protected, so it can be accessed in a derived type.
		std::cout << name << " weights " << weight << "kg.\n";
	}

	// Synthesized destructor is virtual as in a base class.
};

////////////////////////////////////////////////////////////////////////////////

int main() {
	Sword s;
	std::cout << s.Name() << " deals " << s.Damage() << " damage.\n";

	// The left hand side is an object.
	// Even if the function is virtual, the compiler ignores this fact and uses
	// a call to a function from its type's scope:
	//     Sword::print(&s);
	s.print();

	std::cout << "\n";

	// Object slicing
	Weapon w = s;
	std::cout << "Weapon deals " << w.Damage() << " damage.\n";

	// The left hand side is an object copied from a slice of a derived object.
	// Even if the function is virtual, the compiler ignores this fact and uses
	// a call to a function from its type's scope:
	//     Weapon::print(&w);
	w.print();

	std::cout << "\n";

	// An address of an object of a derived class can be assigned
	// to its base class pointer.
	Weapon *wp = &s;
	std::cout << "Weapon deals " << (*wp).Damage() << " damage.\n";
	// The left hand side is a base class pointer to a derived object.
	// If the function is virtual, for pointers and references the compiler uses
	// a hidden pointer (v_ptr) at the beginning of an object to access
	// its type's virtual table in run-time, extract from there the address of
	// a corresponding virtual function and then call it:
	//     (wp->v_ptr[print=0])();
	wp->print();

	std::cout << "\n";

	// An object of a derived class can be bound to its base class reference.
	Weapon& wr = s;
	std::cout << "Weapon deals " << wr.Damage() << " damage.\n";
  
	// The left hand side is a base class reference to a derived object.
	// If the function is virtual, for pointers and references the compiler uses
	// a hidden pointer (v_ptr) at the beginning of an object to access
	// its type's virtual table in run-time, extract from there the address of
	// a corresponding virtual function and then call it:
	//     ((&wr)->v_ptr[print=0])();
	wr.print();
}
