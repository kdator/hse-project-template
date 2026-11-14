#include <iostream>
#include "collection.hpp"

struct Point { int x, y; };

int main() {
    Collection<Point> points;
    points.add(Point{1, 2});
    std::cout << points.size() << '\n';
    // std::cout << joinValues(points) << '\n';   // ошибка: нет Point::myValue()
}
