/*
HLP2: vec-grade-calc.cpp
01/25/2022

This program read a student's midterm, final exam, and an unknown number of
assignment grades and then computes that student's course grade which is then
printed to standard output.
Assume the student's final exam counts for 40% of the final grade, the midterm
exam counts for 20%, and the median homework grade makes up the remaining 40%.
The program exhibits the use of the string, vector, sort algorithm, and
stream manipulators.
*/

#include <iomanip>		// for std::setprecision
#include <ios>				// for std::streamsize
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>	// for std::sort

// local declarations
// overloaded functions to compute course grade
double grade(double midterm, double final, double hw);
double grade(double midterm, double final, const std::vector<double>& hw);
// function to compute median of a set of numbers
double median(std::vector<double> hw);

int main() {
/*
C++ offers a way of saying that a particular name should always be interpreted
as coming from a particular namespace. For example, by writing
  using std::cout;
we can say that we intend to use the name cout to mean std::cout exclusively,
and that we do not intend to define anything named cout ourselves. Once we have
done so, we can say cout instead of std::cout.
Logically enough, such a declaration is called a using-declaration. The name
that it mentions behaves similarly to other names. In short, a using-declaration
introduces a local synonym.

On the other hand, a using-directive makes names from a namespace available
almost as if they had been declared outside their namespaces. For example,
by writing
  using namespace std;
we can say that we intend to use ALL the names declared in namespace std.
Global using-directives are best avoided to reduce the chance of name pollution.
*/

  // ask for and read the student's name
  std::cout << "Please enter your first name: ";
  std::string name;
  std::cin >> name;
  std::cout << "Hello, " << name << "!" << "\n";
  
  // ask for and read the midterm and final grades
  std::cout << "Please enter your midterm and final exam grades: ";
  double midterm, final;
  std::cin >> midterm >> final;
  
  // ask for the homework grades
  std::cout << "Enter all your homework grades, followed by end-of-file: ";
  
  std::vector<double> homework;
  double x;
  while (std::cin >> x) {
    homework.push_back(x);
  }
/*
Testing for end of input:
The effect of the statement
  while (cin >> x) { ... }
is to attempt to read from cin. If the read succeeds, x will hold the value that
we just read, and the while test also succeeds. If the read fails (either because
we have run out of input or because we encountered input that was invalid for the
type of x), then the while test fails, and we should not rely on the value of x.
Understanding how this code works is a bit subtle. Remember that the >>  operator
returns its left operand, so that asking for the value of cin >> x is equivalent to
executing cin >> x and then asking for the value of cin. For example, we can read a
single value into x and test whether we were successful in doing so, by executing
  if (cin >> x) { ... }
This statement has the same meaning as
  cin >> x;
  if (cin) { ... }
Thus, when we use cin >> x as a condition, we aren't just testing the condition; we
are also reading a value into x as a side effect. Now, all we need to do is to figure
out what it means to use cin as a condition in a while statement.
Because cin has type istream, which is part of the standard library, we must look to
the definition of istream for the meaning of if (cin) or while (cin).
As we know, the while or if test a condition, which is an expression that yields a
truth value. The precise type of such a truth value is bool. Using a value of any
arithmetic or pointer type automatically converts the value of type bool, so we
can use values of these types as the expression in a condition. Of course, istream
is neither a pointer nor an arithmetic type. However, the standard library defines a
conversion from type istream to void*. It does so by defining istream::operator void*,
which tests various status flags to determine whether the istream is valid, and
returns either 0 or an implementation-defined nonzero void* value to indicate the
state of the stream.
The reason that class istream defines operator void* rather than operator bool is
to allow the compiler to detect the following erroneous usage:
  int x;
  cin << x; // we should have written cin >> x;
If class istream were to define operator book, this expression would use istream::
operator bool to convert cin to bool, and then convert the resulting bool value to
int, shift that value left by a number of bits equal to the value of x, and throw
the result away! By defining a conversion to void*, rather than to an arithmetic
type, the standard library still allows an istream to be used as a condition, but
prevents it from being used as an arithmetic value.
*/

  // check that the student entered some homework grades
  std::vector<double>::size_type size = homework.size();
  if (0 == size) {
    std::cout << "\nYou must enter your grades. Please try again.\n";
    return 1;
  }
  
  // compute and generate final grade
  double final_grade = grade(midterm, final, homework);
  
  // write the result
  std::streamsize prec = std::cout.precision();
  std::cout	<< "Your final grade is " << std::setprecision(3)
            << final_grade << std::setprecision(prec) << "\n";
/*
Our goal is to write the final grade with three significant digits, which we do
by using setprecision. Like endl, setprecision is a manipulator. However, while
endl is declared in iostream, setprecision is declared in iomanip. setprecision
manipulates the stream by causing subsequent output on that stream to appear
with the given number of significant digits. By writing setprecision(3), we ask
the implementation to write grades with three significant digits, generally two
before the decimal point and one after.
By using setprecision, we change the precision of any subsequent output that
might appear on cout. Because this statement is at the end of the program, we
know that there is no such output. Nevertheless, we believe that it is wise to
resert cout's precision to what it was before we changed it. We do so by calling
a member function of cout named precision. This function tells us the precision
that a stream uses for floating-point output. We use setprecision to set the
precision to 3, write the final grade, and then set the precision back to the
value that precision gave us.
We could have used the precision member function to set the precision, by
writing

  // set precision to 3, return previous value
  streamsize prec = cout.precision(3);
  cout	<< "Your final grade is " << final_grade << endl;
  // reset precision to its original value
  cout.precision(prec);
  
However, we prefer to use the setprecision manipulator, because by doing so,
we can minimize the part of the program in which the precision is set to an
unusual value.
*/	
}

// compute the median of a vector<double> by sorting the values in the container
// and then finding the middle value, or the average of the two middle values if
// we have even number of elements.
// note that we are passing the vector<double> parameter by value because in order
// to compute the median value of a sequence of values, the sequence of values must
// be sorted in ascending (or, descending) order. To facilitate the sorting but yet
// at the same time to ensure that caller's copy of the vector<double> is not altered
// we pass by value.
double median(std::vector<double> vec) {
  using vec_sz = std::vector<double>::size_type; // declare simpler type name
  
  vec_sz size = vec.size();
  std::sort(vec.begin(), vec.end());
  vec_sz mid = size/2;
  return size % 2 == 0 ? (vec[mid]+vec[mid-1])/2.0 : vec[mid];
}

// compute a student's overall grade from midterm and final exam grades
// and homework grade
double grade(double midterm, double final, double homework) {
  return 0.2*midterm + 0.4*final + 0.4*homework;
}

// compute a student's overall grade from midterm and final exam grades and
// vector of homework grades.
// this function does not copy its argument, because median does so for us.
double grade(double midterm, double final, const std::vector<double>& hw) {
  return grade(midterm, final, median(hw));
}
