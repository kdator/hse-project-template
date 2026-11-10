#include "unique.hpp"
#include <cstdio>

struct Widget {
    int id;
    explicit Widget(int i) : id(i) { std::printf("  Widget(%d)\n", id); }
    ~Widget() { std::printf("  ~Widget(%d)\n", id); }
};

int main() {
    {
        UniquePtr<Widget> a(new Widget(1));
        UniquePtr<Widget> b = std::move(a);       // владение передано
        std::printf("a пуст: %d, b->id = %d\n", !a, b->id);
    }                                             // b удаляет Widget(1)
    {
        UniquePtr<Widget[]> arr(new Widget[2]{Widget(10), Widget(11)});
        std::printf("arr[1].id = %d\n", arr[1].id);
    }                                             // delete[]
}
