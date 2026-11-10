#include <cstdio>

template <typename T, typename U>
void f(T, U)   { std::puts("f(T, U)"); }

template <typename T>                       // перегрузка
void f(T, int) { std::puts("f(T, int)"); }

int main() {
    f(1.5, 'c');
    f(1.5, 2);
}
