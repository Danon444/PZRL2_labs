.PHONY: all clean run

TARGET = stack
CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: $(TARGET)

$(TARGET): Stack.o List.o Vector.o StackImplementation.o
	$(CXX) $(CXXFLAGS) Stack.o List.o Vector.o StackImplementation.o -o $(TARGET) -L. -lStackTest

Stack.o: Stack.cpp 
	$(CXX) -c Stack.cpp

List.o: List.cpp 
	$(CXX) -c List.cpp

Vector.o: Vector.cpp 
	$(CXX) -c Vector.cpp

StackImplementation.o: StackImplementation.cpp 
	$(CXX) -c StackImplementation.cpp

clean:
	rm -rf *.o $(TARGET)

run: all
	./$(TARGET)
