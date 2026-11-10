#include "unique.hpp"

#include <cstdio>
#include <memory>

struct Widget {
    int id;
    explicit Widget(int i) : id(i) { std::printf("  Widget(%d)\n", id); }
    ~Widget() { std::printf("  ~Widget(%d)\n", id); }
};

struct FileCloser {                                    // пустой функтор-удалитель
    void operator()(std::FILE* f) const { std::printf("  fclose\n"); std::fclose(f); }
};

int main() {
    {
        UniquePtr<Widget> a(new Widget(1));
        UniquePtr<Widget> b = std::move(a);
        std::printf("a empty: %d, b->id = %d\n", !a, b->id);
    }
    {
        UniquePtr<Widget[]> arr(new Widget[2]{Widget(10), Widget(11)});
        std::printf("arr[1].id = %d\n", arr[1].id);
    }
    {
        UniquePtr<std::FILE, FileCloser> f(std::fopen("/tmp/tpl_demo.txt", "w"));
        std::fputs("hello\n", f.get());
    }
    using FnDel = void (*)(Widget*);
    std::printf("sizeof UniquePtr<Widget>              = %zu\n", sizeof(UniquePtr<Widget>));
    std::printf("sizeof UniquePtr<FILE, FileCloser>    = %zu\n", sizeof(UniquePtr<std::FILE, FileCloser>));
    std::printf("sizeof std::unique_ptr<FILE, FileCloser> = %zu\n", sizeof(std::unique_ptr<std::FILE, FileCloser>));
    std::printf("sizeof std::unique_ptr<Widget, FnDel>    = %zu\n", sizeof(std::unique_ptr<Widget, FnDel>));
#ifdef COPY
    UniquePtr<Widget> c(new Widget(3));
    UniquePtr<Widget> d = c;
#endif
#ifdef DEREF_ARR
    UniquePtr<int[]> z(new int[3]);
    *z;
#endif
}
