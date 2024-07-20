CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

TARGET = main.exe
OBJECTS = main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp BinarySearchTree.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)