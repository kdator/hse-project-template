#include "stack.hpp"

template <typename T>
void Stack<T>::push(const T& v) { data_.push_back(v); }

template <typename T>
T Stack<T>::pop() { T v = data_.back(); data_.pop_back(); return v; }

#ifdef EXPLICIT
template class Stack<int>;          // явное инстанцирование
#endif
