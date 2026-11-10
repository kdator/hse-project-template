CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: convert

convert: convert.cpp
	$(CXX) $(CXXFLAGS) convert.cpp -o $@

run: convert
	./convert && echo "ok"

error:
	@echo '--- ожидаемая ошибка: couldn'\''t deduce template parameter '\''To'\'''
	-$(CXX) $(CXXFLAGS) -c convert_broken.cpp -o /dev/null

clean:
	rm -f convert
.PHONY: all run error clean
