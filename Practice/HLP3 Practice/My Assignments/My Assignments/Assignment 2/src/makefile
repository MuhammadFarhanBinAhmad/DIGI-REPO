# name of C++ compiler
CXX       = g++
# options to C++ compiler
CXX_FLAGS = -std=c++17 -pedantic-errors -Wall -Wextra -Werror -Wconversion
# flag to linker to make it link with math library
LDLIBS    = -lm
# list of object files
OBJS      = driver.o splitter.o
# name of executable program
EXEC      = splitter.out

# by convention the default target (the target that is built when writing
# only make on the command line) should be called all and it should
# be the first target in a makefile
all : $(EXEC)

# however, the problem that arises with the previous rule is that make
# will think all is the name of the target file that should be created
# so, we tell make that all is not a file name
.PHONY : all

# this rule says that target $(EXEC) will be built if prerequisite
# files $(OBJS) have changed more recently than $(EXEC)
# text $(EXEC) will be replaced with value vector.out
# text $(OBJS) will be substituted with list of prerequisites in line 10
# line 31 says to build $(EXEC) using command $(CXX) with
# options $(CXX_FLAGS) specified on line 6
$(EXEC) : $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)

# target vector-driver.o depends on both vector-driver.cpp and vector.h
# and is created with command $(CXX) given the options $(CXX_FLAGS)
splitter.o : splitter.cpp splitter.h
	$(CXX) $(CXX_FLAGS) -c splitter.cpp -o splitter.o

driver.o : driver.cpp splitter.h
	$(CXX) $(CXX_FLAGS) -c driver.cpp -o driver.o

# says that clean is not the name of a target file but simply the name for
# a recipe to be executed when an explicit request is made
.PHONY : clean
# clean is a target with no prerequisites;
# typing the command in the shell: make clean
# will only execute the command which is to delete the object files
clean :
	rm -f $(OBJS) $(EXEC)

# says that rebuild is not the name of a target file but simply the name
# for a recipe to be executed when an explicit request is made
.PHONY : rebuild
# rebuild is for starting over by removing cleaning up previous builds
# and starting a new one
rebuild :
	$(MAKE) clean
	$(MAKE)

.PHONY : test
test : $(EXEC)
	./$(EXEC)

.PHONY : test-mem
test-mem : $(EXEC)
	valgrind ./$(EXEC)

test : $(EXEC)
	./$(EXEC) > your-output.txt

.PHONY : split
split : $(EXEC)
	./$(EXEC) -s 19 -o test_ -i test1 > output.txt

.PHONY : join
join : $(EXEC)
	./$(EXEC) -j -o test1-join -i test_* > output.txt

.PHONY : split1
split1 : $(EXEC)
	./$(EXEC) -s 4096 -o doxy-part_ -i doxygen.pdf > output.txt

.PHONY : join1
join1 : $(EXEC)
	./$(EXEC) -j -o doxygen-join.pdf -i doxy-part_* > output.txt