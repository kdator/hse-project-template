#pragma once
#include <vector>

template <typename T>
class Stack {
public:
    void push(const T& v);
    T pop();
    bool empty() const { return data_.empty(); }
private:
    std::vector<T> data_;
};
