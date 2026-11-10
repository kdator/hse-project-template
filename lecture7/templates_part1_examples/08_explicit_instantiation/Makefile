CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: app

app: main.cpp stack.cpp
	$(CXX) $(CXXFLAGS) main.cpp stack.cpp -o $@

run: app
	./app

error-double:
	@echo '--- ожидаемая ошибка: Stack<double> не инстанцирован в stack.cpp'
	-$(CXX) $(CXXFLAGS) -DUSE_DOUBLE main.cpp stack.cpp -o app_double

fixed-double:
	$(CXX) $(CXXFLAGS) -DUSE_DOUBLE -DDOUBLE main.cpp stack.cpp -o app_double && ./app_double

symbols:
	$(CXX) $(CXXFLAGS) -DDOUBLE -c stack.cpp -o stack.o && nm -C stack.o | grep -E 'Stack<.*>::(push|pop)'

clean:
	rm -f app app_double stack.o
.PHONY: all run error-double fixed-double symbols clean
