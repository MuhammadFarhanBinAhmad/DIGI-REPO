// CSD2125
/*******************************************************************************
 * This example shows a basic inheritance.

 * FlyingMonster (a publicly derived class) inherits from its base class Monster
 * public member functions X(), Y(), Name(), and Scare() but it does not have
 * access to its data members due to encapsulation with a private keyword. It also 
 * specializes the behaviour by adding getZ() relevant only to FlyingMonster objects.
 *
 * Take note about the order of construction (a base class constructor is run
 * before data members of a derived class are initialized and a derived
 * constructor is eventually executed), destruction (a base class destructor is
 * run after a derived class destructor was executed and derived data members
 * have been destroyed.
 *
 * As a base class does not have a default constructor, a derived class must
 * explicitly indicate which its constructor is wants to use; it is done in
 * a constructor initializer list of a derived constructor.
 ******************************************************************************/
#include <iostream>
#include <string>

class Monster {
  std::string n;
  int x, y;
public:
  Monster(std::string const& s, int mx, int my) : n(s), x(mx), y(my) {
    std::cout << "Monster::Monster() - " << s << "\n";
  }
  ~Monster() { std::cout << "Monster::~Monster() - " << n << "\n"; }
  
  int X() const { return x; }
  int Y() const { return y; }
  std::string Name() const { return n; }
  
  void scare() const { std::cout << "Monster " << n << " at (" 
                                 << x << ", " << y << ") says boo!!!\n";
  }
};

class FlyingMonster : public Monster {
  int z;
public:
  FlyingMonster(std::string const& n, int x, int y, int mz)
       : Monster(n, x, y), z(mz) {
    std::cout << "FlyingMonster::FlyingMonster() - " << n << "\n";
  }
  ~FlyingMonster() { std::cout << "FlyingMonster::~FlyingMonster()\n"; }
  
  void scare() const { std::cout << "FlyingMonster " << Name() << 
     " at (" << X() << ", " << Y() << ") says boooooooo!!!\n";
  }
};

class CookieMonster {
  Monster m;
  int     z;
public:
  CookieMonster(std::string const& s, int mx, int my, int mz)
    : m(s, mx, my), z(mz) { 
    std::cout << "CookieMonster::CookieMonster() - " << s << "\n";
  }
  ~CookieMonster() { std::cout << "CookieMonster::~CookieMonster() - " 
                     << m.Name() << "\n";
  }
  std::string Name() const { return m.Name(); }
  int         X()    const { return m.X(); }
  int         Y()    const { return m.Y(); }
  int         Z()    const { return z; }
  
  void laugh() {
    std::cout << "CookieMonster " << Name() << " says hohoho!!!\n";
  }
};

// Objects of base class type can always point to objects of
// derived type
void scare_people(Monster *pm) {
  pm->scare();
}

int main() {
  Monster m("baddude", 10, 20);
  m.scare();
  scare_people(&m);
  
  FlyingMonster fm("reallybaddude", 11, 21, 31);
  fm.scare();
  scare_people(&fm);
}
