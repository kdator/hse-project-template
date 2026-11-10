#include "vector.hpp"
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    Vector<int> v;
    for (int x : {5, 3, 8, 1, 9, 2}) v.push_back(x);

    std::sort(v.begin(), v.end());                       // алгоритм
    for (int x : v) std::printf("%d ", x);               // range-for
    std::printf("\nsum = %d\n", std::accumulate(v.begin(), v.end(), 0));

    std::vector<int> src{10, 20, 30};
    std::copy(src.begin(), src.end(), std::back_inserter(v));
    std::printf("size = %zu, last = %d\n", v.size(), v[v.size() - 1]);
}
