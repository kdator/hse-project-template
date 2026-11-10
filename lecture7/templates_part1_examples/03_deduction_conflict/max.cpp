#include <iostream>
#include <string>

template <typename T>
T maxOf(T a, T b) {
    return a < b ? b : a;
}

int main() {
    std::cout << maxOf(3, 7) << "\n";                       // T = int
    std::cout << maxOf(2.5, 1.5) << "\n";                   // T = double
    std::cout << maxOf(std::string("pear"), std::string("apple")) << "\n";
    std::cout << maxOf<double>(1, 2.5) << "\n";             // T задан явно
#ifdef CONFLICT
    std::cout << maxOf(1, 2.5) << "\n";
#endif
}
