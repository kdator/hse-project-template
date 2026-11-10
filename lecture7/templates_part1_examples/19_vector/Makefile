CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: growth stl

growth: growth.cpp vector.hpp
	$(CXX) $(CXXFLAGS) growth.cpp -o $@

stl: stl.cpp vector.hpp
	$(CXX) $(CXXFLAGS) stl.cpp -o $@

run: all
	./growth && ./stl

error-nodefault:
	@echo '--- ожидаемая ошибка: Vector<Id> без конструктора по умолчанию'
	-$(CXX) $(CXXFLAGS) -DMINE -c nodefault.cpp -o /dev/null

clean:
	rm -f growth stl
.PHONY: all run error-nodefault clean
