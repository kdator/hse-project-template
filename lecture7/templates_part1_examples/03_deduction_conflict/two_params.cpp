#include <iostream>
#include <type_traits>

template <typename T, typename U>
auto maxOf(T a, U b) {                         // C++14: тип результата выводится
    return a < b ? b : a;                      // общий тип int и double — double
}

template <typename To, typename From>
To convert(From x) { return static_cast<To>(x); }

int main() {
    auto m = maxOf(1, 2.5);
    std::cout << m << " " << std::is_same_v<decltype(m), double> << "\n";
    std::cout << convert<int>(3.7) << "\n";    // To задан, From = double выведен
#ifdef NORET
    int y = convert(3.7);
#endif
}
