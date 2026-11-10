#include "unique.hpp"

#include <cstdio>
#include <memory>

struct FileCloser {                              // пустой функтор
    void operator()(std::FILE* f) const {
        std::puts("\tfclose");
        std::fclose(f);
    }
};

using FnDeleter = void (*)(std::FILE*);          // указатель на функцию

using Ours    = UniquePtr<std::FILE, FileCloser>;
using Std     = std::unique_ptr<std::FILE, FileCloser>;
using StdFn   = std::unique_ptr<std::FILE, FnDeleter>;

int main() {
    {
        Ours f(std::fopen("/tmp/demo.txt", "w"));
        std::fputs("hello\n", f.get());
    }                                            // fclose при выходе

    std::printf("UniquePtr<FILE, FileCloser>       %zu\n", sizeof(Ours));
    std::printf("std::unique_ptr<FILE, FileCloser> %zu\n", sizeof(Std));
    std::printf("std::unique_ptr<FILE, FnDeleter>  %zu\n", sizeof(StdFn));
}
