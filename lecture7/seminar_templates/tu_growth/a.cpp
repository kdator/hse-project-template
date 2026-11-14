#include "algos.hpp"

long fa() {
    std::vector<int> v{3, 1, 4, 1, 5};
    return sumAll(v) + maxElement(v) + countGreater(v, 2);
}
