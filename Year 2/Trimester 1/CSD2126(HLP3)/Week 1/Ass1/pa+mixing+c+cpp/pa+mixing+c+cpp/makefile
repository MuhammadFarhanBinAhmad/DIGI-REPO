# name of C++ compiler
CXX       = g++
# options to C++ compiler
CXX_FLAGS = -std=c++11 
#name of C compiler
COO		  = gcc
#options to C compiler
COO_FLAGS = -std=c11 


.PHONY : compile
compile1 : 
	$(COO) $(COO_FLAGS) -c driver.c -o c-driver.o
	$(COO) $(COO_FLAGS) -c splitter.c -o c-splitter.o
	$(COO) $(COO_FLAGS) c-driver.o c-splitter.o -o compile1.out

compile2 : 
	$(CXX) $(CXX_FLAGS) -c driver.cpp -o cpp-driver.o
	$(CXX) $(CXX_FLAGS) -c splitter.cpp -o cpp-splitter.o
	$(CXX) $(CXX_FLAGS) cpp-driver.o cpp-splitter.o -o compile2.out

compile3 : 
	$(CXX) $(CXX_FLAGS) -c driver.cpp -o cpp-driver.o
	$(COO) $(COO_FLAGS) -c splitter.c -o c-splitter.o
	$(CXX) $(CXX_FLAGS) cpp-driver.o c-splitter.o -o compile3.out

compile4 : 
	$(CXX) $(CXX_FLAGS) -c driver.cpp -o cpp-driver.o
	$(CXX) $(CXX_FLAGS) -c splitter.c -o c-splitter.o
	$(CXX) $(CXX_FLAGS) cpp-driver.o c-splitter.o -o compile4.out