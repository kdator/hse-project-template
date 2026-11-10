#include "stack.hpp"

#include <cstdio>
#include <string>

int main() {
    Stack<int> a;          a.push(1);
    Stack<std::string> b;  b.push("hello");

    std::printf("%d %s\n", a.pop(), b.pop().c_str());
#ifdef USE_DOUBLE
    Stack<double> c;       c.push(2.5);
#endif
}
