# Define the compiler to use (e.g. gcc, g++)
CC = g++

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
#
INCLUDES = -I./src/include

# Define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L./test/UnitTest++

# Define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lUnitTest++

.PHONY: depend clean

# Run UnitTest++ makefile
all: UnitTestLib ./test/Fp32Test.o
	
	# Run Fp32 unit tests:
	@./test/Fp32Test.o
	
#./test/Fp32Test.o : ./test/Fp32Test.cpp ./src/include/Fp32.hpp UnitTestLib
	# Compile unit tests
#	g++ ./test/Fp32Test.cpp -L./test/UnitTest++ -lUnitTest++ -o ./test/Fp32Test.o

	
SRC_CPP_FILES := $(wildcard src/*.cpp)
SRC_OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_CPP_FILES:.cpp=.o)))
SRC_LD_FLAGS := 
SRC_CC_FLAGS := -Wall -g

TEST_CPP_FILES := $(wildcard test/*.cpp)
TEST_OBJ_FILES := $(addprefix obj/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))
TEST_LD_FLAGS := 
TEST_CC_FLAGS := -Wall -g

# Compiles source code
#src: $(SRC_OBJ_FILES)
	# Compiling src1
	#g++ $(LD_FLAGS) -o $@ $^
	

	
# Compiles unit test code
# Unit test code
test: $(TEST_OBJ_FILES) $(SRC_OBJ_FILES) | UnitTestLib
	# Compiling unit test code
	#g++ $(TEST_LD_FLAGS) -o $@ $^ -L./test/UnitTest++ -lUnitTest++
	g++ $(TEST_LD_FLAGS) -o obj/test $^ -L./test/UnitTest++ -lUnitTest++
	
	# Run Fp32 unit tests:
	@./obj/test

# Generic rule for test object files
obj/%.o: test/%.cpp
	g++ $(TEST_CC_FLAGS) -c -o $@ $<
	
# This next line is a generic rule to compile to an object file
obj/%.o: src/%.cpp
	# Compiling src2
	g++ $(SRC_CC_FLAGS) -c -o $@ $<
	
UnitTestLib:
	# Compile UnitTest++ library (has it's own Makefile)
	$(MAKE) -C ./test/UnitTest++/ all
	
clean:
	# Clean UnitTest++ library (has it's own Makefile)
	$(MAKE) -C ./test/UnitTest++/ clean
	
	# Clean everything else
	@echo " Cleaning..."; $(RM) *.o *~
	@echo " Cleaning..."; $(RM) ./obj/*
	
depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it