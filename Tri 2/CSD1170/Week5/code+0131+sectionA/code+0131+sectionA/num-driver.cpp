#include <iostream>
#include "num.hpp"

//When similar function comes out, they will if the "perfect one" exist.
int foo(Num m)
{
  std::cout << "n: " << n << "/n";
  return n.Int()+1;
}
int foo(int x)
{
  return x+1;
}

bool boo (std::vector<int> vi)
{
  return vi.empty();
}

int main() {

  foo(static_cast<Num>(11));
  boo(1'000'000);

  Num n0;
  std::cout << "n0: " << n0 << "\n";
  n0.set_val(11);
  std::cout << "n0: " << n0 << "\n";

  Num n1 {11};
  std::cout << "n1: " << n1 << "\n";

  Num n2{n1};
  std::cout << "n2: " << n2 << '\n';
  n2 = n0;
  std::cout << "n2: " << n2 << '\n';

  n2 = 99; //static_cast<Num>(99);
  std::cout << "n2: " << n2 << '\n';


  n2 = n0 + n1; // n2.op=(n0.op+(n1))
  n2 = 1 + n0;
  n2 = n0 + 1;
  std::cout << "n2: " << n2 << '\n';

  n2 += n1;
  std::cout << "n2: " << n2 << '\n';



}