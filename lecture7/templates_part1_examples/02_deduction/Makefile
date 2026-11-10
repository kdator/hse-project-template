CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

run: main
	./main

error-rvalue:
	@echo '--- ожидаемая ошибка: T& не принимает rvalue'
	-$(CXX) $(CXXFLAGS) -DRVAL -c main.cpp -o /dev/null

clean:
	rm -f main
.PHONY: all run error-rvalue clean
