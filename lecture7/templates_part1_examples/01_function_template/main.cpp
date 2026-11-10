template <typename T>
T maxOf(T a, T b) {
    return a < b ? b : a;
}

int main() {
    maxOf(3, 7);
    maxOf(2.5, 1.5);
    maxOf<double>(1, 2.5);
}
