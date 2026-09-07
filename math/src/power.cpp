#include <power.hpp>
#include <multiply.hpp>

double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) {
        result = multiply(result, base);
    }
    return result;
}
