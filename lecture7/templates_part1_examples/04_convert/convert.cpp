#include <string>

template <typename To, typename From>
To convert(From from) {
    return static_cast<To>(from);
}

int main() {
    convert<int>(3.7);

    // int result = convert(3.7);
    // ^^^^
    // Данная строчка сломана. Компилятор не может
    // вывести тип для возвращаемого значения, так как ему он явно не указан / 
    // не передан параметр с нужным типом.
    // В комментарии к выводу компиляции вы увидите: .. couldn't deduce template parameter 'To'.
    // Требует явного указания convert<int>(3.7)

    return 0;
}
