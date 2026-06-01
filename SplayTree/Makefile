.PHONY: all run clean

TEST=test

all: $(TEST)
	
$(TEST): main.cpp
	 g++ main.cpp -o $(TEST) -Wall -Wextra

run: all
	./$(TEST)

clean:
	rm -rf *.o $(TEST)
