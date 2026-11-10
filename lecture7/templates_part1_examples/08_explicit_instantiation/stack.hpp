#pragma once

#include <vector>

template <typename T>
class Stack {
public:
    void push(const T& v);
    T pop();
private:
    std::vector<T> data_;
};
