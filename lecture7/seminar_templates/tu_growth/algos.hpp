#pragma once
#include <string>
#include <vector>

template <typename T>
T sumAll(const std::vector<T>& v) {
    T total{};
    for (const T& x : v) total = total + x;
    return total;
}

template <typename T>
T maxElement(const std::vector<T>& v) {
    T best = v.front();
    for (const T& x : v)
        if (best < x) best = x;
    return best;
}

template <typename T>
std::size_t countGreater(const std::vector<T>& v, const T& bound) {
    std::size_t n = 0;
    for (const T& x : v)
        if (bound < x) ++n;
    return n;
}
