#include "algos.hpp"

long fc() {
    std::vector<int> vi{9, 8};
    std::vector<double> vd{1.5};
    std::vector<std::string> vs{"tem", "pla", "tes"};
    return sumAll(vi) + static_cast<long>(maxElement(vd))
         + sumAll(vs).size() + maxElement(vs).size() + countGreater(vs, std::string("p"));
}
