#include <strategy_factory.hpp>

#include <algorithm>
#include <cctype>
#include <filesystem>

#include <json_strategy.hpp>
#include <xlsx_strategy.hpp>

namespace reader {
namespace {

// Расширение файла в нижнем регистре: "Data/Report.XLSX" -> ".xlsx"
std::string lowercaseExtension(const std::string& path) {
    std::string ext = std::filesystem::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return ext;
}

}  // namespace

std::unique_ptr<IReadStrategy> makeReadStrategy(const std::string& path) {
    const std::string ext = lowercaseExtension(path);

    // Единственное место с ветвлением по формату. Добавить поддержку, например,
    // .sql — значит написать класс SqlReadStrategy и дописать здесь одну ветку;
    // ни main.cpp, ни остальные стратегии при этом не меняются.
    if (ext == ".json") {
        return std::make_unique<JsonReadStrategy>();
    }
    if (ext == ".xlsx") {
        return std::make_unique<XlsxReadStrategy>();
    }

    return nullptr;  // формат не поддерживается
}

}  // namespace reader
