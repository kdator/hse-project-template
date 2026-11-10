#include <cstddef>
template <typename T, std::size_t N> struct FixedArray { T data_[N]; };
std::size_t readSize();
enum class Mode { Fast, Safe };
template <Mode M> struct Engine { static constexpr bool safe = (M == Mode::Safe); };
int main() {
    const std::size_t a = 5;      FixedArray<int, a> x{};
    constexpr std::size_t b = 5;  FixedArray<int, b> y{};
    (void)x; (void)y;
    static_assert(Engine<Mode::Safe>::safe);
#ifdef PLAIN
    std::size_t n = 5;            FixedArray<int, n> z;
#endif
#ifdef READ
    const std::size_t m = readSize();  FixedArray<int, m> w;
#endif
}
