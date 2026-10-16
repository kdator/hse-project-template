#include <divide.hpp>
#include <multiply.hpp>

// деление реализовано через умножение на обратную величину
double divide(double a, double b) {
    return multiply(a, 1.0 / b);
}
