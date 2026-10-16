#pragma once

#include <read_strategy.hpp>

namespace reader {

// Стратегия чтения JSON: разбирает файл библиотекой nlohmann/json
// и печатает его обратно с отступом в 2 пробела (pretty-print).
//
// Обратите внимание: в этом заголовке НЕТ #include <nlohmann/json.hpp>.
// Публичный интерфейс класса не упоминает типы из сторонней библиотеки,
// поэтому про json знает только json_strategy.cpp. Именно это позволяет
// слинковать библиотеку с нашей целью как PRIVATE (см. reader/CMakeLists.txt).
class JsonReadStrategy final : public IReadStrategy {
public:
    // override — указание компилятору проверить, что мы действительно
    // перекрываем виртуальную функцию базового класса, а не создаём новую
    // (например, из-за опечатки в имени или другого набора параметров).
    void read(const std::string& path) const override;
    std::string name() const override;
};

}  // namespace reader
