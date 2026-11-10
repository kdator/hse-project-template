CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: error

error:
	@echo '--- ожидаемая ошибка: undefined reference'
	-$(CXX) $(CXXFLAGS) main.cpp stack.cpp -o app

explicit:
	$(CXX) $(CXXFLAGS) -DEXPLICIT main.cpp stack.cpp -o app && ./app

clean:
	rm -f app
.PHONY: all error explicit clean
