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

template <typename T> void Stack<T>::push(const T& v) { data_.push_back(v); }

template <typename T> T Stack<T>::pop() { T v = data_.back(); data_.pop_back(); return v; }
