CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: max two_params

max: max.cpp
	$(CXX) $(CXXFLAGS) max.cpp -o $@

two_params: two_params.cpp
	$(CXX) $(CXXFLAGS) two_params.cpp -o $@

run: all
	./max && ./two_params

error-conflict:
	@echo '--- ожидаемая ошибка: maxOf(1, 2.5)'
	-$(CXX) $(CXXFLAGS) -DCONFLICT -c max.cpp -o /dev/null

clean:
	rm -f max two_params
.PHONY: all run error-conflict clean
