CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0
INST     = 'sumAll<|maxElement<|countGreater<'

all: report

%.o: %.cpp algos.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

app1: a.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp a.o -o $@
app2: a.o b.o main.cpp
	$(CXX) $(CXXFLAGS) -DUSE_B main.cpp a.o b.o -o $@
app3: a.o b.o c.o main.cpp
	$(CXX) $(CXXFLAGS) -DUSE_B -DUSE_C main.cpp a.o b.o c.o -o $@

report: a.o b.o c.o app1 app2 app3
	@echo "Объектные файлы (файл / код .text, байт / число инстанциаций):"
	@for f in a.o b.o c.o; do \
	  printf "  %-14s %8s %4s\n" $$f $$(size $$f | awk 'NR==2{print $$1}') $$(nm -C $$f | grep -cE $(INST)); \
	done
	@echo "Программа (сборка / код .text, байт / число инстанциаций):"
	@printf "  %-14s %8s %4s\n" "app1=a"     $$(size app1 | awk 'NR==2{print $$1}') $$(nm -C app1 | grep -cE $(INST))
	@printf "  %-14s %8s %4s\n" "app2=a+b"   $$(size app2 | awk 'NR==2{print $$1}') $$(nm -C app2 | grep -cE $(INST))
	@printf "  %-14s %8s %4s\n" "app3=a+b+c" $$(size app3 | awk 'NR==2{print $$1}') $$(nm -C app3 | grep -cE $(INST))

symbols: a.o b.o c.o app3
	@for f in a.o b.o c.o app3; do echo "== $$f"; nm -C $$f | grep -E $(INST) | sed -E 's/^[0-9a-f]+ [A-Za-z] //; s/std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >/std::string/g; s/, std::allocator<[a-z:]+ ?> >/>/g' | sort; done

run: app3
	./app3

clean:
	rm -f *.o app1 app2 app3
.PHONY: all report symbols run clean
