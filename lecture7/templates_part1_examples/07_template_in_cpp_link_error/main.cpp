#include "stack.hpp"

#include <cstdio>

int main() {
    Stack<int> s;
    s.push(1); s.push(2);
    std::printf("%d\n", s.pop());
}
