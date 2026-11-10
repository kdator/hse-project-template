CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: trap fixed

trap: trap.cpp
	$(CXX) $(CXXFLAGS) trap.cpp -o $@

fixed: fixed.cpp
	$(CXX) $(CXXFLAGS) fixed.cpp -o $@

run: all
	./trap && ./fixed

clean:
	rm -f trap fixed
.PHONY: all run clean
