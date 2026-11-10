#include <cstddef>
#include <cstdio>
#include <type_traits>

template <typename T, std::size_t N>
class FixedArray {
public:
    constexpr std::size_t size() const { return N; }
    T& operator[](std::size_t i) { return data_[i]; }
    const T& operator[](std::size_t i) const { return data_[i]; }
    T* begin() { return data_; }
    T* end() { return data_ + N; }
private:
    T data_[N];                         // память внутри объекта, без new
};

template <typename T, std::size_t N>
constexpr std::size_t countOf(const T (&)[N]) { return N; }   // как std::size

template <auto V>                         // C++17: тип параметра выводится
struct Constant { static constexpr auto value = V; };

int main() {
    FixedArray<int, 3> a{};
    FixedArray<int, 4> b{};
    for (int& x : a) x = 7;
    std::printf("sizeof a = %zu, sizeof b = %zu\n", sizeof a, sizeof b);
    std::printf("same type: %d\n", std::is_same_v<decltype(a), decltype(b)>);
    int raw[] = {1, 2, 3, 4, 5};
    std::printf("countOf(raw) = %zu\n", countOf(raw));
    std::printf("Constant<42>: %d, Constant<'x'>: %c\n", Constant<42>::value, Constant<'x'>::value);
    static_assert(FixedArray<double, 8>{}.size() == 8);
#ifdef ASSIGN
    a = b;
#endif
#ifdef RUNTIME
    std::size_t n = 5;
    FixedArray<int, n> c;
#endif
}
#ifdef DOUBLE
template <double X> struct Scale {};
#endif
