#include <file_content.hpp>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace reader {

FileContent::FileContent(std::string fileName, std::vector<uint8_t> bytes)
    : bytes_(std::move(bytes)), fileName_(std::move(fileName)) {}

FileContent::FileContent(std::string fileName, const std::string& text)
    : bytes_(text.begin(), text.end()), fileName_(std::move(fileName)) {}

FileContent FileContent::fromFile(const std::string& path) {
    // std::ios::binary — читаем байты как есть, без преобразования переводов строк.
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("не удалось открыть файл: " + path);
    }
    std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                               std::istreambuf_iterator<char>());
    return FileContent(path, std::move(bytes));
}

FileContent& FileContent::operator+=(const std::string& text) {
    // char → uint8_t конвертируется поэлементно при вставке диапазона.
    bytes_.insert(bytes_.end(), text.begin(), text.end());
    return *this;
}

FileContent FileContent::operator+(const std::string& text) const {
    FileContent result = *this;  // копия
    result += text;
    return result;
}

bool FileContent::operator==(const FileContent& other) const {
    return fileName_ == other.fileName_ && bytes_ == other.bytes_;
}

std::size_t FileContentHasher::operator()(const FileContent& content) const {
    // Константы 64-битного FNV-1a.
    constexpr uint64_t kOffsetBasis = 14695981039346656037ULL;
    constexpr uint64_t kPrime = 1099511628211ULL;

    uint64_t hash = kOffsetBasis;
    auto mix = [&hash](uint8_t byte) {
        hash ^= byte;
        hash *= kPrime;
    };

    for (char c : content.fileName()) {
        mix(static_cast<uint8_t>(c));
    }

    // Разделитель между именем и байтами: без него пары
    // ("ab", "c...") и ("a", "bc...") хэшировались бы одинаково.
    mix(0xFF);

    const auto& bytes = content.bytes();
    const std::size_t n = std::min(bytes.size(), kPrefixSize);
    for (std::size_t i = 0; i < n; ++i) {
        mix(bytes[i]);
    }

    return static_cast<std::size_t>(hash);
}

}  // namespace reader
