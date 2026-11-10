import sys

if __name__ == "__main__":
    k = int(sys.argv[1])
    print('#include "vector.hpp"\n#include <algorithm>\n#include <cstdio>')

    for i in range(k):
        print(f'struct S{i} {{ int v; bool operator<(const S{i}& o) const {{ return v < o.v; }} }};')

    print('int main() {\n    long total = 0;')
    for i in range(k):
        print(f'    {{ Vector<S{i}> v; for (int j = 0; j < 100; ++j) v.push_back(S{i}{{(j * 37) % 101}});\n      std::sort(v.begin(), v.end()); total += v[0].v; }}')

    print('    std::printf("%ld\\n", total);\n}')
