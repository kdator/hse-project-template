CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

run: main
	./main

symbols: main
	nm -C main | grep 'Box<Point>'

error-print:
	@echo '--- ожидаемая ошибка: вызов b.print() для Point'
	-$(CXX) $(CXXFLAGS) -c main_print.cpp -o /dev/null

clean:
	rm -f main
.PHONY: all run symbols error-print clean
