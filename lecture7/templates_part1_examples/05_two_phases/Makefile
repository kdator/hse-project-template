CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0

phase1:
	@echo '--- ожидаемая ошибка: ошибка при чтении шаблона'
	-$(CXX) $(CXXFLAGS) -c phase1.cpp -o /dev/null

phase2:
	@echo '--- ожидаемая ошибка: ошибка при инстанцировании'
	-$(CXX) $(CXXFLAGS) -c phase2.cpp -o /dev/null

all: phase1 phase2
.PHONY: all phase1 phase2
