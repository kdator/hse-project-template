CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

all: fixed_array

fixed_array: fixed_array.cpp
	$(CXX) $(CXXFLAGS) fixed_array.cpp -o $@

run: fixed_array
	./fixed_array

check-values:
	$(CXX) $(CXXFLAGS) -c nttp_values.cpp -o /dev/null && echo "const, constexpr, enum: ok"

error-plain:
	@echo '--- ожидаемая ошибка: std::size_t n = 5'
	-$(CXX) $(CXXFLAGS) -DPLAIN -c nttp_values.cpp -o /dev/null

error-read:
	@echo '--- ожидаемая ошибка: const n = readSize()'
	-$(CXX) $(CXXFLAGS) -DREAD -c nttp_values.cpp -o /dev/null

error-double:
	@echo '--- ожидаемая ошибка: template <double X> в C++17'
	-$(CXX) $(CXXFLAGS) -DDOUBLE -c fixed_array.cpp -o /dev/null

error-assign:
	@echo '--- ожидаемая ошибка: FixedArray<int,3> = FixedArray<int,4>'
	-$(CXX) $(CXXFLAGS) -DASSIGN -c fixed_array.cpp -o /dev/null

clean:
	rm -f fixed_array
.PHONY: all run check-values error-plain error-read error-double error-assign clean
