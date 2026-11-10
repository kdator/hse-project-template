CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

run: main
	./main && echo "ok"

asm: main.cpp
	$(CXX) $(CXXFLAGS) -fcf-protection=none -fno-asynchronous-unwind-tables -masm=intel -S main.cpp -o - | c++filt | grep -vE '^\s*\.cfi|^\.L(FB|FE|CFI)' | sed -n '/^.*maxOf<.*>(.*):/,/ret/p'

symbols: main
	nm -C main | grep maxOf

clean:
	rm -f main
.PHONY: all run asm symbols clean
