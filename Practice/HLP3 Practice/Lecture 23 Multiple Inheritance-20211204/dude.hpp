// CS2125 11/30
// dude.hpp
// -- Dude class
#ifndef DUDE_HPP
#define DUDE_HPP

#include <string>
#include <cstdlib>

class Dude {
public:
  Dude(std::string const& s) : mName(s) {}
  virtual ~Dude()                       {}
  std::string const& name() const { return mName; }
  virtual bool punch() const      { return std::rand()%2 == 0; }
private:
  std::string mName;
};

class BadDude : public Dude {
public:
  BadDude(std::string const& s) : Dude(s) {}
  // keyword override is telling both humans and compilers that punch is a
  // virtual function declared in the base class Dude and that derived class
  // BadDude is overriding the base class's implementation.
  virtual bool punch() const override { return std::rand()%3 != 0; }
};

class SubDude : public Dude {
public:
  SubDude(std::string const& s) : Dude(s) {}
  virtual bool punch() const override { return false; }
  // the lack of keyword override is telling both humans and compilers that
  // squonk is not a virtual function declared in a base class.
  virtual bool squonk() const { return std::rand()%2 == 0; }
};

class MajorDude : public BadDude {
public:
  MajorDude(std::string const& s) : BadDude(s) {}
  // lack of keyword override is telling both humans and compilers
  // that stab is not a virtual function previously declared in a base class.
  virtual bool stab() const     { return std::rand()%2 == 0; }
};

class OddDude : public SubDude, public BadDude {
public:
  OddDude(std::string const& s) : SubDude(s), BadDude(s) {}
};

class GodDude : public MajorDude {
public:
  GodDude(std::string const& s) : MajorDude(s) {}
  virtual bool punch() const override { return true; }
  virtual bool stab() const override  { return true; }
};

#endif
