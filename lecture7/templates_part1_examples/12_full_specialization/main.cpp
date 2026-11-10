#include <cmath>
#include <iostream>

template <class T>
bool equal(T a, T b) { return a == b; }

template <>
bool equal(double a, double b) { return std::fabs(a - b) < 1e-9; }


int main() {
    std::cout << std::boolalpha << equal(3.5, 3.5) << std::endl;

    std::cout << std::boolalpha << equal(3, 3) << std::endl;

    return 0;
}
