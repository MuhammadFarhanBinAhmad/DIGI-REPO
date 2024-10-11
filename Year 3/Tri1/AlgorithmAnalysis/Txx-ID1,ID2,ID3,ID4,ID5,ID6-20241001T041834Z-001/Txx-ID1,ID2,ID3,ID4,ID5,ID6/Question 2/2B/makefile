# name of C++ compiler
CXX       = g++
# options to C++ compiler
CXX_FLAGS = -std=c++17 -pedantic-errors -Wall -Wextra -Werror
# flag to linker to make it link with math library
#LDLIBS    = -lm
# list of object files
OBJS      = main.cpp
# name of executable program
EXEC      = a.out

all : $(EXEC)

.PHONY : all

$(EXEC) :
	$(CXX) $(CXX_FLAGS) $(OBJS) -O2 -o $(EXEC) $(LDLIBS)

.PHONY : clean

clean :
	rm -f $(EXEC)

.PHONY : rebuild

rebuild :
	$(MAKE) clean
	$(MAKE)

.PHONY : test


test : $(EXEC)
	./$(EXEC) > output.txt
#	diff -y --strip-trailing-cr --suppress-common-lines 
