CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

N = 20

measure:
	@for opt in -O0 -O2; do for e in 0 1; do \
	  rm -rf ext; python3 gen2.py $(N) $$e; \
	  s=$$(date +%s.%N); (cd ext && for f in *.cpp; do g++ -std=c++17 $$opt -c $$f; done); e2=$$(date +%s.%N); \
	  g++ ext/*.o -o ext/app; \
	  printf "%s extern=%s  .o total=%8d  program .text=%7s  compile=%.2fs\n" $$opt $$e \
	    $$(cat ext/*.o | wc -c) $$(size ext/app | awk 'NR==2{print $$1}') $$(echo "$$e2 - $$s" | bc); \
	done; done

clean:
	rm -rf ext
.PHONY: measure clean
