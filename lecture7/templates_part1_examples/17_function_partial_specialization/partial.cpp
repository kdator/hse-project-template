template <typename T, typename U>
void f(T, U) {}

template <typename T>
void f<T, int>(T, int) {}   // частичная специализация

int main() {}
