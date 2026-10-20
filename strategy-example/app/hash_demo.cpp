// ======================================================================================
//  hashdemo: FileContent и FileContentHasher без файлов на диске.
//
//  filereader использует unordered_map<FileContent, ...> «по делу», а здесь
//  на маленьких примерах видно то, что в filereader не заметно:
//  operator+ / operator+=, коллизию хэшей и почему ключ нельзя менять на месте.
// ======================================================================================

#include <iostream>
#include <string>
#include <unordered_map>

#include <file_content.hpp>

using reader::FileContent;
using reader::FileContentHasher;

using FileIndex = std::unordered_map<FileContent, std::string, FileContentHasher>;

static void printIndex(const FileIndex& index) {
    FileContentHasher hasher;
    for (const auto& [file, note] : index) {
        std::cout << "  " << file.fileName() << " (" << file.bytes().size() << " байт)"
                  << "  hash=" << hasher(file) << "  bucket=" << index.bucket(file)
                  << "  -> " << note << "\n";
    }
}

int main() {
    // ---------------------------------------------------------------- 1. operator+ / +=
    std::cout << "== operator+ и operator+= ==\n";

    FileContent readme("readme.txt", "Hello");
    readme += ", world";                         // меняет readme на месте
    FileContent longer = readme + "!";           // readme не меняется, создаётся копия
    std::cout << "  readme: " << readme.bytes().size() << " байт, "
              << "longer: " << longer.bytes().size() << " байт\n\n";

    // ---------------------------------------------------------------- 2. FileContent как ключ
    std::cout << "== FileContent как ключ ==\n";

    FileIndex index;
    index[readme] = "приветствие";
    index[FileContent("config.ini", "[core]\nverbose = true\n")] = "настройки";
    index.emplace(FileContent("empty.bin", std::vector<uint8_t>{}), "пустой файл");

    // Поиск по равному (но другому) объекту: хэш совпадёт, operator== вернёт true.
    FileContent sameAsReadme("readme.txt", "Hello, world");
    std::cout << "  find(копия readme): "
              << (index.count(sameAsReadme) ? index.at(sameAsReadme) : "не найден") << "\n";
    std::cout << "  find(longer):       "
              << (index.count(longer) ? index.at(longer) : "не найден") << "\n\n";

    // ---------------------------------------------------------------- 3. коллизия
    // Хэшер смотрит только на имя и первые 32 байта. Два файла ниже совпадают
    // по обоим признакам, но различаются хвостом. Хэши равны, а ключи — разные:
    // operator== их различает, и в map окажутся ОБА элемента в одной корзине.
    std::cout << "== коллизия: одно имя, одинаковые первые 32 байта ==\n";

    const std::string header(32, '#');           // 32 одинаковых байта
    FileContent v1("log.txt", header + "version 1");
    FileContent v2("log.txt", header + "version 2");
    index[v1] = "первый";
    index[v2] = "второй";

    FileContentHasher hasher;
    std::cout << "  hash(v1) == hash(v2): " << std::boolalpha << (hasher(v1) == hasher(v2))
              << ",  v1 == v2: " << (v1 == v2) << "\n";
    std::cout << "  элементов в корзине v1: " << index.bucket_size(index.bucket(v1)) << "\n\n";

    // ---------------------------------------------------------------- 4. изменение ключа
    // Ключи в unordered_map константные: index.begin()->first имеет тип
    // const FileContent, и `index.begin()->first += "x"` не скомпилируется.
    // Иначе хэш ключа поменялся бы, а элемент остался бы в старой корзине —
    // и найти его стало бы невозможно.
    //
    // С C++17 ключ можно законно поменять: вынуть узел (extract),
    // изменить ключ и вставить обратно — элемент попадёт в правильную корзину.
    std::cout << "== изменение ключа через extract ==\n";

    auto node = index.extract(readme);
    node.key() += "!";                           // теперь ключ равен longer
    index.insert(std::move(node));
    std::cout << "  find(readme): " << (index.count(readme) ? "найден" : "не найден")
              << ",  find(longer): " << (index.count(longer) ? index.at(longer) : "не найден")
              << "\n\n";

    std::cout << "== весь индекс: " << index.size() << " элементов, "
              << index.bucket_count() << " корзин ==\n";
    printIndex(index);

    return 0;
}
