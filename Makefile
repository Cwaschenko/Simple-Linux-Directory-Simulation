CXX = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS = -std=c++14 -g -Wall

OBJECTS = node.o filesystem.o terminal.o

main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test-all: test-1-node test-2-filesystem-create test-3-filesystem-move test-4-filesystem-remove

test-1-node: test/test-1-node.cpp node.o test/catch/catch.o
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-2-filesystem-create: test/test-2-filesystem-create.cpp filesystem.o node.o test/catch/catch.o
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-3-filesystem-move: test/test-3-filesystem-move.cpp filesystem.o node.o test/catch/catch.o
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-4-filesystem-remove: test/test-4-filesystem-remove.cpp filesystem.o node.o test/catch/catch.o
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* main test/*.o test/test-1-node test/test-2-filesystem-create test/test-3-filesystem-move test/test-4-filesystem-remove test/catch/catch.o
