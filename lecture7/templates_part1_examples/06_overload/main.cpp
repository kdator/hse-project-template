#include <cstdio>

template <typename T> void show(T)  { std::puts("show(T)"); }    // (1)
template <typename T> void show(T*) { std::puts("show(T*)"); }   // (2)
void show(int)                      { std::puts("show(int)"); }  // (3)

int main() {
    int x = 1;
    show(42);
    show(42L);
    show(&x);
    show<>(42);
}
