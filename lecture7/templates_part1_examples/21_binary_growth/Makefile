CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

KS = 1 10 50 100

measure:
	@printf "%-6s %-12s %-10s %s\n" K text symbols seconds
	@for k in $(KS); do \
	  python3 gen.py $$k > b$$k.cpp; \
	  s=$$(date +%s.%N); g++ -std=c++17 -O2 b$$k.cpp -o b$$k; e=$$(date +%s.%N); \
	  printf "%-6s %-12s %-10s %.2f\n" $$k $$(size b$$k | awk 'NR==2{print $$1}') \
	    $$(nm -C b$$k | grep -cE '\bS[0-9]+\b') $$(echo "$$e - $$s" | bc); \
	done

icf: b100.cpp
	g++ -std=c++17 -O2 b100.cpp -o b100 && size b100
	g++ -std=c++17 -O2 -ffunction-sections -fuse-ld=gold -Wl,--icf=all b100.cpp -o b100_icf && size b100_icf

b100.cpp:
	python3 gen.py 100 > b100.cpp

clean:
	rm -f b*.cpp b1 b10 b50 b100 b100_icf
.PHONY: measure icf clean
