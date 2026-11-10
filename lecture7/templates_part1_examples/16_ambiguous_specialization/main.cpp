#include <iostream>
#include <typeinfo>

template <typename T, typename U> struct Pair {
    static void print() { std::cout << "общий шаблон\n"; }
};

template <typename T> struct Pair<T, int> {
    static void print() {
        std::cout << "Pair<T, int>, T = " << typeid(T).name() << '\n';
    }
};

template <typename U> struct Pair<int, U> {
    static void print() {
        std::cout << "Pair<int, U>, U = " << typeid(U).name() << '\n';
    }
};

int main() {
    Pair<double, char>::print();
    Pair<double, int>::print();
    Pair<int, double>::print();
    // Pair<int, int>::print();   — неоднозначность
}
