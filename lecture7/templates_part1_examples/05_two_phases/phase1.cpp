// Функции process и report нигде не объявлены.

template <typename T>
void f(T x) {
    process(x);   // аргумент зависит от T: поиск откладывается до инстанцирования
    report();     // от T не зависит: ошибка при чтении шаблона
}

int main() {}
