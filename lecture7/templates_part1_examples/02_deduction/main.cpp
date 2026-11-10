#include <cstdio>
#include <string_view>

template <typename T>
constexpr std::string_view typeName() {          // имя T из __PRETTY_FUNCTION__ (g++)
    std::string_view p = __PRETTY_FUNCTION__;
    auto b = p.find("T = ") + 4;
    return p.substr(b, p.find(";", b) - b);
}

template <typename T> void byValue(T)      { std::printf("  byValue:  T = %.*s\n", (int)typeName<T>().size(), typeName<T>().data()); }
template <typename T> void byRef(T&)       { std::printf("  byRef:    T = %.*s\n", (int)typeName<T>().size(), typeName<T>().data()); }
template <typename T> void byCRef(const T&){ std::printf("  byCRef:   T = %.*s\n", (int)typeName<T>().size(), typeName<T>().data()); }

int main() {
    int x = 1;
    const int cx = 2;
    int& rx = x;
    int arr[3] = {};

    std::printf("x (int):\n");          byValue(x);   byRef(x);   byCRef(x);
    std::printf("cx (const int):\n");   byValue(cx);  byRef(cx);  byCRef(cx);
    std::printf("rx (int&):\n");        byValue(rx);  byRef(rx);  byCRef(rx);
    std::printf("arr (int[3]):\n");     byValue(arr); byRef(arr); byCRef(arr);
    std::printf("\"hi\":\n");           byValue("hi"); byRef("hi"); byCRef("hi");
    std::printf("42:\n");               byValue(42);  byCRef(42);
#ifdef RVAL
    byRef(42);
#endif
}
