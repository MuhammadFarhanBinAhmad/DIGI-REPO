// HLP3: 05/17
// Code sample to illustrate new[]/delete[] and text file I/O!!!
// Use with grades1.txt to compute average grade!!!
// The pattern represented by this program:
//
// Open an input file stream
// Continue only if the stream state is in a good state
// Attempt to read some input
// Check the stream state
// If the state is good, process the input
// If the state is not good, assume expected eof condition and continue processing

#include <iostream>
#include <fstream>

double compute_avg(double const * first, double const *last) {
  double sum {0.};
  int count {0};
  while (first != last) {
    sum += *first++;
    ++count;
  }
  return sum/static_cast<double>(count);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " input-text-file\n";
    return 1;
  }

/*
A stream object has a set of internal bits as data members that "remember"
the state of the stream. Normally the stream is in the good state if it has
been opened successfully and has not had a problem. An error turns on one
of the error bits, and then the stream is no longer good, and the bit stays
on until it is cleared with the clear() member function. Once an error bit
is turned on, any I/O operation on the stream does nothing. So it is only
valid to read from or write to a stream that is in the good state. There
are member functions for testing the stream state. The names of these stream
states, member functions, and bits are not very well chosen, so read the
following carefully. As you will see, bad is not the exact opposite of good,
and there are multiple ways to fail, only one of which is really bad. If you
try to open a file and it fails to open (e.g. the filename is wrong), the
stream object goes into a not-good state; if you want to try to open it again
(e.g. with the right filename), you must first call the clear() member function
to reset the error bits.
*/
  std::ifstream ifs {argv[1]};
	
/*
The hardware or system software has a malfunction or the file doesn't exist -
this is a "hard" I/O error that your program typically can do nothing about
except try to muddle through (maybe it won't happen a second time) or quit.
This type of error sets the bad bit in the stream object, and the stream is
no longer good. Fortunately, these are rare (unless you have flakey hardware).

Because ifs is of type std::ifstream, we must look to the definition of
class std::ifstream for the meaning of if (ifs).
Looking at the definition of std::ios (from which std::ifstream is derived),
we can see that class std::ios provides a conversion function that can be
used to convert std::ios into a bool value that can be used in the if
statement's condition expression.
Whether the bool value is true or false depends on the internal state of
the std::ifstream object, which will be in a not-good state if the file
could not be opened!!!
*/
  if (!ifs) {
    std::cerr << "Unable to open file " << argv[1] << "\n";
    return 1;
  }

  int count {0};
  double dtmp;
#if 0
  while (1) {
    ifs >> dtmp;
    if (!ifs.good()) {
      break;
    }
    ++count;
  }
#else
  // this is simpler code than the above ...
  // The expression ifs >> dtmp evaluates to a reference to ifs, so that asking
  // for the value of ifs >> dtmp in the while statement's condition is
  // equivalent to evaluating ifs >> dtmp and then asking for the value of
  // ifs >> dtmp.
  // Because ifs is of type std::ifstream, we must look to the definition of
  // class std::ifstream for the meaning of while (ifs).
  // Looking at the definition of std::ios (from which std::ifstream is derived),
  // we can see that class std::ios provides a conversion function that can be
  // used to convert std::ios into a bool value that can be used in the while
  // statement's condition expression.
  // Whether the bool value is true or false depends on the internal state of
  // the std::ifstream object, which will remember whether the most recent
  // attempt to read has worked. Thus using std::ifstream as a condition is
  // equivalent to testing whether the last attempt to read from std::ifstream
  // was successful. The read attempt won't be successful when end of file is
  // reached. In that case too, expression ifs >> dtmp will evaluate to false.
  while (ifs >> dtmp) {
    ++count;
  }
#endif

  double *pi = new double [count];
/*
Once an error bit is turned on, any I/O operation on the stream does nothing.
So it is only valid to read from or write to a stream that is in the good state.
Because object ifs is in a bad state, we must clear its state to a good state
and also reset the file offset location to start of file!!!
*/
  ifs.clear(std::ios_base::goodbit);
  ifs.seekg(0);
  int i {0};
  while (i < count) {
    ifs >> pi[i++];
  }

  double avg = compute_avg(pi, pi+count);
  std::cout << "Average grade: " << avg << "\n";
  delete [] pi;
}

/*
A more paranoid version:

  Open the input stream state 
  Continue only if the stream state is in a good state

  Attempt to read some input
  Check the stream state
  If the state is good, process the input
  If the state is not good, do the following:
    If the state is eof, then handle an end-of-file condition:
      If an eof is expected and normal, continue processing
      Otherwise, it is an error; print a message, and take appropriate action
  If the state is bad bit; print a message and terminate
  If the state is fail due to invalid input, do the following:
    Print a message informing the user of the bad input
    Clear the stream state with the clear() function
    Skip the offending material
    Resume processing
*/