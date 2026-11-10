#include <string>

struct Point { int x, y; };                     // нет operator<

template <typename T>
T maxOf(T a, T b) { return a < b ? b : a; }

int main() {
    Point p{1, 2}, q{3, 4};
    maxOf(p, q);
}
