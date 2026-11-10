CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

run: main
	./main

error:
	@echo '--- ожидаемая ошибка: ambiguous template instantiation'
	-$(CXX) $(CXXFLAGS) -c main_ambiguous.cpp -o /dev/null

clean:
	rm -f main
.PHONY: all run error clean
