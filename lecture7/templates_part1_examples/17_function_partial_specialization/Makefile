CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: overload

overload: overload.cpp
	$(CXX) $(CXXFLAGS) overload.cpp -o $@

run: overload
	./overload

error:
	@echo '--- ожидаемая ошибка: partial specialization is not allowed'
	-$(CXX) $(CXXFLAGS) -c partial.cpp -o /dev/null

clean:
	rm -f overload
.PHONY: all run error clean
