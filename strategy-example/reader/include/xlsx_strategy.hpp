#pragma once

#include <read_strategy.hpp>

namespace reader {

// Стратегия чтения xlsx: открывает книгу библиотекой OpenXLSX, берёт первый лист
// и печатает его как ASCII-таблицу с рамкой из символов +, - и |.
class XlsxReadStrategy final : public IReadStrategy {
public:
    void read(const std::string& path) const override;
    std::string name() const override;
};

}  // namespace reader
