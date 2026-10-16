#include <json_strategy.hpp>

#include <fstream>
#include <iostream>
#include <stdexcept>

// Заголовок сторонней библиотеки подключается только в .cpp — см. комментарий
// в json_strategy.hpp. Библиотека header-only: весь её код компилируется
// прямо здесь, вместе с нашим файлом.
#include <nlohmann/json.hpp>

namespace reader {

void JsonReadStrategy::read(const std::string& path) const {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("не удалось открыть файл: " + path);
    }

    // json::parse бросает nlohmann::json::parse_error (наследник std::exception),
    // если файл не является корректным JSON. Мы его не перехватываем:
    // исключение долетит до main.cpp, где обрабатываются ошибки всех стратегий.
    const nlohmann::json data = nlohmann::json::parse(in);

    // dump(2) сериализует объект обратно в текст с отступом в 2 пробела.
    // Поэтому компактный JSON в одну строку выводится в читаемом виде.
    std::cout << data.dump(2) << "\n";
}

std::string JsonReadStrategy::name() const {
    return "JSON (nlohmann/json)";
}

}  // namespace reader
