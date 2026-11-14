#include "algos.hpp"

long fb() {
    std::vector<int> vi{2, 7, 1};
    std::vector<double> vd{2.5, 0.5, 9.0};
    return sumAll(vi) + maxElement(vi)
         + static_cast<long>(sumAll(vd) + maxElement(vd)) + countGreater(vd, 1.0);
}
