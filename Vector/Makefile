TARGET = test
CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: $(TARGET)

$(TARGET): Vector.cpp 
	$(CXX) $< -o $(TARGET) -L. -lVectorTest $(CXXFLAGS)

clean:
	rm -rf *.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
