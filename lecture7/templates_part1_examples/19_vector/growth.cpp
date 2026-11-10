#include "vector.hpp"
#include <cstdio>
#include <vector>

int main() {
    Vector<int> v;
    std::vector<int> sv;
    for (int i = 0; i < 6; ++i) {
        v.push_back(i);
        sv.push_back(i);
        std::printf("size %zu: Vector %zu, std::vector %zu\n",
                    v.size(), v.capacity(), sv.capacity());
    }
}
