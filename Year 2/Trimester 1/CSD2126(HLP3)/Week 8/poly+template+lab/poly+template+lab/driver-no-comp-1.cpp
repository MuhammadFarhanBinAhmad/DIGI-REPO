#include "polynomial.h"
#include <iostream>

// the purpose of this driver is to test [through unsuccessful compilation] that
// polynomials with different types [say, int and float] cannot be multiplied!!!
int main() {   
  std::cout << "-------- " << __func__ << " --------\n";
  
  HLP3::Polynomial<int,2> p2;
  p2[0] = 1;
  p2[1] = -2;
  p2[2] = 1;
  std::cout << p2 << std::endl;

  HLP3::Polynomial<int,5> p5;
  p5[0] = 3;
  p5[1] = -2;
  p5[2] = 1;
  p5[3] = 1;
  p5[4] = -1;
  p5[5] = 1;
  std::cout << p5 << std::endl;
  
  HLP3::Polynomial<int,7> p7_1 = p2*p5;
  HLP3::Polynomial<int,7> p7_2 = p5*p2; // should be commutative

  int values[] = { 1,2,3,4,5 };
  for ( int i=0; i<5; ++i ) {
    int r1 = p2(values[i]);
    int r2 = p5(values[i]);
    int r3 = p7_1(values[i]);
    int r4 = p7_2(values[i]);
    std::cout << r3 << " " << r4 << std::endl;
    if ( r1*r2 != r3 or r1*r2 != r4 ) {
      std::cout << "Error\n";
    }
  }
}
