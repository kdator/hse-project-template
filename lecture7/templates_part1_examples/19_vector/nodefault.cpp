#include "vector.hpp"
#include <vector>
struct Id { explicit Id(int v) : v(v) {} int v; };   // нет конструктора по умолчанию
int main() {
    std::vector<Id> a;  a.push_back(Id(1));           // ок
#ifdef MINE
    Vector<Id> b;       b.push_back(Id(1));
#endif
}
