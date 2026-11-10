#include <cstdio>

template <typename T> void g(T)          { std::puts("(a) g(T)"); }
template <>           void g<int*>(int*) { std::puts("(c) g<int*>"); }
template <typename T> void g(T*)         { std::puts("(b) g(T*)"); }

int main() {
    int x = 0;
    g(&x);
}
