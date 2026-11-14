CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: main

main: main.cpp collection.hpp types.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

run: main
	./main

clean:
	rm -f main
.PHONY: all run clean

error-point:
	@echo '--- ожидаемая ошибка: у Point нет метода myValue()'
	-$(CXX) $(CXXFLAGS) -c point_error.cpp -o /dev/null
.PHONY: error-point
