#include <cstdio>

template <typename T> void g(T)  { std::puts("(a) g(T)"); }
template <typename T> void g(T*) { std::puts("(b) g(T*)"); }
void g(int*)                     { std::puts("(d) g(int*)"); }   // перегрузка

int main() {
    int x = 0;
    g(&x);
}
