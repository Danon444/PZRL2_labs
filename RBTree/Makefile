.PHONY: all clean run

all: test

test: RBTree.cpp
	g++ RBTree.cpp -o test -L. -lRBTreeTest
run: all
	./test
clean:
	rm -rf *.o test
