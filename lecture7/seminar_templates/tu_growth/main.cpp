#include <cstdio>

long fa();
#ifdef USE_B
long fb();
#endif
#ifdef USE_C
long fc();
#endif

int main() {
    long r = fa();
#ifdef USE_B
    r += fb();
#endif
#ifdef USE_C
    r += fc();
#endif
    std::printf("result = %ld\n", r);
}
