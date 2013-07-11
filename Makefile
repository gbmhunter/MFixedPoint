# Define the compiler to use (e.g. gcc, g++)
CC = g++

# Define any compile-time flags (e.g. -Wall, -g)
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES = -I./src/include

# Define library paths in addition to /usr/lib
LFLAGS = -L./test/UnitTest++

# Define any libraries to link into executable:
# The 'lib' prefix and the .a file extension must be removed, and
# an -l prefix added, e.g. to link in
# libMyLibrary.a, you would add -lMyLibrary
LIBS = -lUnitTest++
	
SRC_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRC_LD_FLAGS := 
SRC_CC_FLAGS := -Wall -g

TEST_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard test/*.cpp))
TEST_LD_FLAGS := 
TEST_CC_FLAGS := -Wall -g
	
.PHONY: depend clean

# Compile everything and run unit tests
all: UnitTestLib Test
	
	# Run unit tests:
	@./test/FpTest.out
	
# Make fixed-point library
FpLib: $(SRC_OBJ_FILES)
	# Make Fp library
	ar r libFp.a $(SRC_OBJ_FILES)

# Generic rule for src object files
src/%.o: src/%.cpp
	# Compiling src2
	g++ $(SRC_CC_FLAGS) -c -o $@ $<
	
# Unit test code
Test: $(TEST_OBJ_FILES) | FpLib UnitTestLib
	# Compiling unit test code
	g++ $(TEST_LD_FLAGS) -o ./test/FpTest.out $(TEST_OBJ_FILES) -L./test/UnitTest++ -lUnitTest++ -L./ -lFp

# Generic rule for test object files
test/%.o: test/%.cpp
	g++ $(TEST_CC_FLAGS) -c -o $@ $<
	
# Unit test library
UnitTestLib:
	# Compile UnitTest++ library (has it's own Makefile)
	$(MAKE) -C ./test/UnitTest++/ all

# Clean everything
clean:
	# Clean UnitTest++ library (has it's own Makefile)
	$(MAKE) -C ./test/UnitTest++/ clean
	
	# Clean everything else
	@echo " Cleaning..."; $(RM) ./*.a
	@echo " Cleaning..."; $(RM) ./src/*.o
	@echo " Cleaning..."; $(RM) ./test/*.o
	@echo " Cleaning..."; $(RM) ./test/*.out
	