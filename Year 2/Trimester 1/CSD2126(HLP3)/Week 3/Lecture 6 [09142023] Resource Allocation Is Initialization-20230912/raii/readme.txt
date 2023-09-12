Compile and link the raii source files like this:

g++ -std=c++17 -pedantic-errors -Wall -Wextra -Werror mstr.cpp raii.cpp -o raii.out

Execute like this:

valgrind ./raii.out

and observe that there are no memory leaks even though exceptions are thrown on
partially constructed objects [during their construction].
