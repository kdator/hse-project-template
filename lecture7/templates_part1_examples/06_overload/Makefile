CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

run: main
	./main

clean:
	rm -f main
.PHONY: all run clean
