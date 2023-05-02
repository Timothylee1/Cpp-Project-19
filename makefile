# name of C++ compiler
CXX       = g++
# options to C++ compiler
CXX_FLAGS = -std=c++17 -pedantic-errors -Wall -Wextra -Werror
# flag to linker to make it link with math library
LDLIBS    = -lm
# list of object files
OBJS      = s.o spelling.o
# name of executable program
EXEC      = s.out

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
# text $(EXEC) will be replaced with value spelling.out
# text $(OBJS) will be substituted with list of prerequisites in line 10
# line 31 says to build $(EXEC) using command $(CXX) with
# options $(CXX_FLAGS) specified on line 6
$(EXEC) : $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)

# target spelling-driver.o depends on both spelling-driver.cpp and spelling.hpp
# and is created with command $(CXX) given the options $(CXX_FLAGS)
s.o : spelling-driver.cpp spelling.hpp #spelling.cpp
	$(CXX) $(CXX_FLAGS) -c spelling-driver.cpp -o s.o

# target spelling.o depends on both spelling.cpp and spelling.hpp
# and is created with command $(CXX) given the options $(CXX_FLAGS)
spelling.o : spelling.cpp spelling.hpp
	$(CXX) $(CXX_FLAGS) -c spelling.cpp -o spelling.o

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

.PHONY : 1 2 3 4 0 
0 : 1 2 3 4 

0 : $(EXEC)
	./$(EXEC) > o0.txt  
	diff -y --strip-trailing-cr --suppress-common-lines o0.txt testall.txt

1 : $(EXEC)
	./$(EXEC) 1 > o1.txt  
	diff -y --strip-trailing-cr --suppress-common-lines o1.txt test1.txt
	
2 : $(EXEC)
	./$(EXEC) 2 > o2.txt 
	diff -y --strip-trailing-cr --suppress-common-lines o2.txt test2.txt
	
3 : $(EXEC)
	./$(EXEC) 3 > o3.txt 
	diff -y --strip-trailing-cr --suppress-common-lines o3.txt test3.txt
 
4 : $(EXEC)
	./$(EXEC) 4 > o4.txt 
	diff -y --strip-trailing-cr --suppress-common-lines o4.txt test4.txt
 