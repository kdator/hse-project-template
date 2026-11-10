CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

OBJS = a.o b.o main.o

all: app

%.o: %.cpp stack.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

app: $(OBJS)
	$(CXX) $(OBJS) -o $@

symbols: app
	@for f in a.o b.o app; do echo "== $$f"; nm -C $$f | grep 'Stack<int>::push'; done

clean:
	rm -f $(OBJS) app
.PHONY: all symbols clean
