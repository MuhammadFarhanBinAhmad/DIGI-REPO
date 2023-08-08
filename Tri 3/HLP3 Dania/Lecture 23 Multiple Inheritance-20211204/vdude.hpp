// CS2125 11/30
// vdude.hpp
// -- Dude class, virtual version
// Any time you've an inheritance hierarchy with more than one path between
// a base class and a derived class (or the "multiple inheritance diamond"),
// the data members of the base class will be replicated for each of the paths.
// If that's not what you want, you must make the class with the data a
// virtual base class. To do that, you have all classes that immediately inherit
// from it use virtual inheritance (VI).

#ifndef VDUDE_HPP
#define VDUDE_HPP

#include <string>
#include <cstdlib>

class Dude {
  public:
    Dude(std::string const& s) : mName(s) {}
    virtual ~Dude(void)                 {}
    std::string const& name(void) const { return mName; }
    virtual bool punch(void) const      { return std::rand()%2 == 0; }
  private:
    std::string mName;
};

// Avoiding the replication of base classes requires some extra behind-the-scenes
// work by compilers, and the result is that objects created from classes using 
// VI are generally larger than they would be without VI. Access to data members
// in virtual base classes is also slower than to those in non-virtual base classes.
// The details vary from compiler to compiler but the basic idea is that VI costs.
// Another problem is that the rules governing the initialization of virtual base 
// classes are more complicated and less intuitive than are those for non-virtual 
// bases. The responsibility for initializing a virtual base is borne by the most 
// derived class in the hierarchy.
// Notice the differences in the constructors for classes MajorDude, OddDude, and
// GodDude in MI here and without VI in dude.hpp.
// Implications of this rule include: (1) classes derived from virtual bases that
// require initialization must be aware of their virtual bases, no matter how far
// high and distant the bases are, and (2) when a new derived class is added to the
// hierarchy, it must assume initialization responsibilities for its virtual bases
// (both direct and indirect). The basic advice about VI is simple:
// (1) Don't use virtual bases unless you need to. By default, use non-VI, and 
// (2) If you must use virtual base classes, avoid putting data in them - that way,
// you don't have to worry about oddities in the initialization rules for such classes.

class SubDude : public virtual Dude {
  public:
    SubDude(std::string const& s) : Dude(s) {}
    bool punch(void) const override { return false; }
    virtual bool squonk(void) const { return std::rand()%2 == 0; }
};

class BadDude : public virtual Dude {
  public:
    BadDude(std::string const& s) : Dude(s) {}
    bool punch(void) const override { return std::rand()%3 != 0; }
};

class MajorDude : public BadDude {
  public:
    MajorDude(std::string const& s) : Dude(s), BadDude(s) {}
    virtual bool stab(void) const   { return std::rand()%2 == 0; }
};

class OddDude : public SubDude, public BadDude {
  public:
    OddDude(std::string const& s) : Dude(s), SubDude(s), BadDude(s) {}
    bool punch(void) const override { return BadDude::punch(); }
};

class GodDude : public MajorDude {
  public:
    GodDude(std::string const& s) : Dude(s), MajorDude(s) {}
    bool punch(void) const override { return true; }
    bool stab(void) const override  { return true; }
};

#endif
