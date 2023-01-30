/*
To make external variable x - which by default has external linkage -
have internal linkage, add keyword static to declaration statement.
This will ensure that the compiler will not export this name to
the linker. That is, the name x will be private to this source file.
*/
// definition of external variable with external linkage
double const x = 3.14159265359;  // pi

// compute circle's area
double area(double radius) {
  return x*radius*radius;
}

// compute circle's circumference
double circumference(double radius) {
  return 2.0*x*radius;
}
