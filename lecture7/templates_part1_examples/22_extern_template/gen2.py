import sys
import os

if __name__ == "__main__":
    n = int(sys.argv[1]); ext = sys.argv[2] == '1'
    os.makedirs('ext', exist_ok=True)

    for i in range(n):
        with open(f'ext/tu{i}.cpp', 'w') as ostream:
            ostream.write('#include "../vector.hpp"\n#include <string>\n#include <algorithm>\n')
            if ext:
                ostream.write('extern template class Vector<std::string>;\n')
            ostream.write(f'std::size_t f{i}() {{ Vector<std::string> v; for (int j = 0; j < 10; ++j) v.push_back(std::to_string(j * {i+3}));\n'
                    f'  Vector<std::string> c = v; std::sort(c.begin(), c.end()); return c.size() + c[0].size(); }}\n')

    with open('ext/main.cpp','w') as ostream:
        ostream.write('#include "../vector.hpp"\n#include <string>\n#include <cstdio>\n')
        if ext:
            ostream.write('template class Vector<std::string>;\n')
        for i in range(n):
            ostream.write(f'std::size_t f{i}();\n')
        ostream.write('int main() { std::size_t s = 0;\n'+''.join(f' s += f{i}();\n' for i in range(n)) + ' std::printf("%zu\\n", s); }\n')
