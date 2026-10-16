#include <xlsx_strategy.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <OpenXLSX.hpp>

namespace reader {
namespace {

// Ширина строки на экране в символах, а не в байтах.
// В UTF-8 русская буква занимает 2 байта, поэтому s.size() для строки "Отдел"
// вернёт 10, и рамка таблицы разъехалась бы. Считаем только ведущие байты:
// у продолжающих байтов старшие биты равны 10xxxxxx.
std::size_t displayWidth(const std::string& s) {
    std::size_t width = 0;
    for (unsigned char byte : s) {
        if ((byte & 0xC0) != 0x80) {
            ++width;
        }
    }
    return width;
}

// Горизонтальная линия рамки: +------+-----+
void printSeparator(const std::vector<std::size_t>& widths) {
    std::cout << '+';
    for (std::size_t width : widths) {
        std::cout << std::string(width + 2, '-') << '+';
    }
    std::cout << '\n';
}

// Одна строка таблицы: | значение | значение |
void printRow(const std::vector<std::string>& cells, const std::vector<std::size_t>& widths) {
    std::cout << '|';
    for (std::size_t i = 0; i < widths.size(); ++i) {
        const std::string& text = cells[i];
        // Выравнивание по левому краю: текст, затем добивка пробелами до нужной ширины.
        // std::setw здесь не подходит — он считает байты, а не символы.
        std::cout << ' ' << text << std::string(widths[i] - displayWidth(text) + 1, ' ') << '|';
    }
    std::cout << '\n';
}

}  // namespace

void XlsxReadStrategy::read(const std::string& path) const {
    using namespace OpenXLSX;

    XLDocument doc;
    // OpenXLSX бросает исключения, унаследованные от std::runtime_error,
    // если файла нет или он не является корректным xlsx-архивом.
    doc.open(path);

    const std::vector<std::string> sheets = doc.workbook().worksheetNames();
    if (sheets.empty()) {
        doc.close();
        throw std::runtime_error("в книге нет ни одного листа: " + path);
    }

    // По условию в файле одна таблица, поэтому берём первый лист.
    XLWorksheet sheet = doc.workbook().worksheet(sheets.front());
    const std::string sheetName = sheet.name();
    const uint32_t rows = sheet.rowCount();
    const uint16_t cols = sheet.columnCount();

    // Шаг 1. Считываем все ячейки в строки. Любой тип ячейки (число, строка,
    // bool, пустая) печатается через operator<< библиотеки OpenXLSX.
    std::vector<std::vector<std::string>> table(rows, std::vector<std::string>(cols));
    for (uint32_t r = 1; r <= rows; ++r) {
        for (uint16_t c = 1; c <= cols; ++c) {
            std::ostringstream cell;
            cell << sheet.cell(r, c).value();
            table[r - 1][c - 1] = cell.str();
        }
    }
    // Все данные уже лежат в table, документ можно закрыть. После close()
    // объекты sheet и cell ссылаются на освобождённую память, поэтому имя листа
    // мы сохранили в sheetName заранее.
    doc.close();

    // Шаг 2. Ширина каждого столбца — максимум по всем его ячейкам.
    std::vector<std::size_t> widths(cols, 0);
    for (const std::vector<std::string>& row : table) {
        for (std::size_t c = 0; c < row.size(); ++c) {
            widths[c] = std::max(widths[c], displayWidth(row[c]));
        }
    }

    // Шаг 3. Печатаем рамку. Первая строка листа считается заголовком таблицы
    // и отделяется дополнительной линией.
    std::cout << "лист \"" << sheetName << "\": " << rows << " строк, " << cols << " столбцов\n";
    printSeparator(widths);
    for (std::size_t r = 0; r < table.size(); ++r) {
        printRow(table[r], widths);
        if (r == 0) {
            printSeparator(widths);
        }
    }
    printSeparator(widths);
}

std::string XlsxReadStrategy::name() const {
    return "XLSX (OpenXLSX)";
}

}  // namespace reader
