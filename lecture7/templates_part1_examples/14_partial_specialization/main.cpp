#include <iostream>
#include <typeinfo>
#include <vector>

template <typename T> struct Describe {                 // общий шаблон
    static void print() { std::cout << "общий шаблон, T = " << typeid(T).name() << '\n'; }
};

template <> struct Describe<bool> {                     // полная
    static void print() { std::cout << "полная специализация для bool\n"; }
};

template <typename T> struct Describe<T*> {             // частичная
    static void print() { std::cout << "указатель, T = " << typeid(T).name() << '\n'; }
};

template <typename T, std::size_t N> struct Describe<T[N]> {
    static void print() { std::cout << "массив, T = " << typeid(T).name() << ", N = " << N << '\n'; }
};

template <typename T> struct Describe<std::vector<T>> {
    static void print() { std::cout << "vector, T = " << typeid(T).name() << '\n'; }
};

int main() {
    Describe<int>::print();
    Describe<bool>::print();
    Describe<int*>::print();
    Describe<int**>::print();
    Describe<double[4]>::print();
    Describe<std::vector<char>>::print();
}
