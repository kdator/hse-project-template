#include <iostream>
#include <multiply.hpp>
#include <divide.hpp>
#include <power.hpp>

int main() {
    double a = 3.0;
    double b = 4.0;

    std::cout << a << " * " << b << " = " << multiply(a, b) << "\n";
    std::cout << a << " / " << b << " = " << divide(a, b)   << "\n";
    std::cout << a << "^3"        << " = " << power(a, 3)   << "\n";

    return 0;
}
