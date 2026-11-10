#include <iostream>
#include <typeinfo>

template <typename T> struct Kind {                     // общий шаблон
    static void print() { std::cout << "общий шаблон, T = " << typeid(T).name() << '\n'; }
};

template <typename T> struct Kind<T*> {                 // любой указатель
    static void print() { std::cout << "Kind<T*>, T = " << typeid(T).name() << '\n'; }
};

template <typename T> struct Kind<const T*> {           // указатель на const
    static void print() { std::cout << "Kind<const T*>, T = " << typeid(T).name() << '\n'; }
};

int main() {
    Kind<int>::print();
    Kind<int*>::print();
    Kind<const int*>::print();
    Kind<const char**>::print();
}
