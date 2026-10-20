#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// ======================================================================================
//  FileContent как ключ std::unordered_map
// ======================================================================================
//
//  FileContent — содержимое файла: имя + сырые байты. filereader складывает
//  уже обработанные файлы в
//
//      std::unordered_map<FileContent, std::string, FileContentHasher>
//
//  и не печатает повторно файл, который уже встречался в аргументах.
//
//  Чтобы тип мог быть ключом unordered_map, контейнеру нужны две операции:
//
//      1. Hash     — функция «ключ → size_t», по которой выбирается корзина (bucket).
//      2. KeyEqual — сравнение ключей, чтобы внутри корзины найти нужный элемент.
//
//  По умолчанию unordered_map берёт std::hash<Key> и std::equal_to<Key>.
//  std::hash<FileContent> не существует, поэтому хэшер пишем сами
//  (FileContentHasher ниже) и передаём третьим шаблонным параметром,
//  а std::equal_to просто вызывает operator==, который определён в классе.
//
//  Главное правило, связывающее эти две функции:
//
//      a == b   ⇒   hash(a) == hash(b)
//
//  Обратное НЕ требуется: разные ключи с одинаковым хэшем — это коллизия,
//  она легальна и лишь замедляет поиск (в корзине оказывается несколько элементов).
// ======================================================================================

namespace reader {

class FileContent {
public:
    FileContent() = default;
    FileContent(std::string fileName, std::vector<uint8_t> bytes);
    FileContent(std::string fileName, const std::string& text);

    // Читает файл с диска целиком в двоичном режиме; имя — переданный путь.
    // Бросает std::runtime_error, если файл не открывается.
    static FileContent fromFile(const std::string& path);

    const std::string& fileName() const { return fileName_; }
    const std::vector<uint8_t>& bytes() const { return bytes_; }

    // Дописывает в конец bytes_ все байты строки text.
    // Возвращает ссылку на себя, чтобы работали цепочки: (a += "x") += "y".
    FileContent& operator+=(const std::string& text);

    // Не меняет текущий объект: возвращает новый FileContent = копия + text.
    // Реализован через operator+= — так логика дописывания живёт в одном месте.
    FileContent operator+(const std::string& text) const;

    // Нужен unordered_map (через std::equal_to) для сравнения ключей.
    // Сравниваем ВСЁ: и имя, и все байты, а не только первые 32.
    bool operator==(const FileContent& other) const;
    bool operator!=(const FileContent& other) const { return !(*this == other); }

private:
    std::vector<uint8_t> bytes_;
    std::string fileName_;
};

// Пользовательский хэшер — обычная структура с operator(), то есть функциональный
// объект (функтор). unordered_map хранит его экземпляр и вызывает hasher(key)
// каждый раз, когда нужно понять, в какую корзину положить или где искать ключ.
//
// Хэш считается по имени файла и ПЕРВЫМ 32 БАЙТАМ содержимого:
//   + быстро даже для гигабайтных файлов — не нужно хэшировать их целиком;
//   − файлы с одинаковым именем и одинаковым началом дадут один хэш (коллизия).
// Правило «a == b ⇒ hash(a) == hash(b)» при этом соблюдается: равные объекты
// совпадают целиком, а значит, совпадают и их первые 32 байта.
//
// Сама функция — FNV-1a (Fowler–Noll–Vo): для каждого байта
// hash ^= byte; hash *= FNV_PRIME. Простая и с неплохим перемешиванием.
struct FileContentHasher {
    static constexpr std::size_t kPrefixSize = 32;

    // const обязателен: контейнер вызывает хэшер через константную ссылку.
    std::size_t operator()(const FileContent& content) const;
};

}  // namespace reader
