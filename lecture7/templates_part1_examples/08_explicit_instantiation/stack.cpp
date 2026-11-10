#include "stack.hpp"
#include <string>

template <typename T>
void Stack<T>::push(const T& v) { data_.push_back(v); }

template <typename T>
T Stack<T>::pop() { T v = data_.back(); data_.pop_back(); return v; }

// явное инстанцирование: заранее известный список типов
template class Stack<int>;
template class Stack<std::string>;
#ifdef DOUBLE
template class Stack<double>;
#endif
