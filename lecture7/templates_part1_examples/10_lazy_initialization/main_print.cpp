#include <iostream>

template <class T>
class Box {
public:
    explicit Box(T value) : value_(std::move(value)) { }

    const T& get() const { return value_; }

    void print() const { std::cout << value_ << std::endl; }

private:
    T value_;
};

struct Point { int x, y; };

int main() {
    Box<Point> b{Point{1, 2}};
    std::cout << b.get().x << std::endl;

    b.print();
    // ^^^
    // Обратите внимание, что код выше работает и компилируется ровно до момента, пока мы
    // явно не позовем функцию Box<T>::print(). Более того, вы не увидите ее инстанциации
    // в коде ассемблера в Explorer.

    return 0;
}
