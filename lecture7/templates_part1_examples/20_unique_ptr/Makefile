CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: unique deleter ebo

unique: unique.cpp unique.hpp
	$(CXX) $(CXXFLAGS) unique.cpp -o $@

deleter: deleter.cpp unique.hpp
	$(CXX) $(CXXFLAGS) deleter.cpp -o $@

ebo: ebo.cpp
	$(CXX) $(CXXFLAGS) ebo.cpp -o $@

run: all
	./unique && ./deleter && ./ebo

error-copy:
	@echo '--- ожидаемая ошибка: копирование UniquePtr'
	-$(CXX) $(CXXFLAGS) -DCOPY -c errors.cpp -o /dev/null

error-deref:
	@echo '--- ожидаемая ошибка: *z для UniquePtr<int[]>'
	-$(CXX) $(CXXFLAGS) -DDEREF_ARR -c errors.cpp -o /dev/null

clean:
	rm -f unique deleter ebo
.PHONY: all run error-copy error-deref clean
