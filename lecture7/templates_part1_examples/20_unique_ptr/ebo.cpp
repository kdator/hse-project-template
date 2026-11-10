#include <cstdio>

struct Empty { void operator()(int*) const {} };   // нет полей

struct AsMember { int* p; Empty d; };              // пустой член класса
struct AsBase : private Empty { int* p; };         // пустая база

int main() {
    std::printf("sizeof(Empty)    = %zu\n", sizeof(Empty));
    std::printf("sizeof(AsMember) = %zu\n", sizeof(AsMember));
    std::printf("sizeof(AsBase)   = %zu\n", sizeof(AsBase));
}
