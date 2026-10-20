// ======================================================================================
//  CLI: ./filereader data/employees.xlsx data/config.json ...
//
//  Для каждого аргумента командной строки фабрика выбирает подходящую стратегию
//  чтения, и программа печатает содержимое файла в консоль. Файл, который уже
//  встречался в аргументах (то же имя и те же байты), второй раз не печатается.
// ======================================================================================

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <file_content.hpp>
#include <strategy_factory.hpp>

int main(int argc, char* argv[]) {
    // argv[0] — путь к самой программе, аргументы начинаются с argv[1].
    if (argc < 2) {
        std::cerr << "использование: " << argv[0] << " <файл> [файл ...]\n"
                  << "поддерживаемые форматы: .json, .xlsx\n";
        return 1;
    }

    // Один указатель на всю программу. На каждой итерации в него подставляется
    // стратегия, подходящая текущему файлу.
    //
    // unique_ptr — владеющий указатель: он единственный владелец объекта и
    // удаляет его в деструкторе. При присваивании нового значения предыдущая
    // стратегия автоматически удаляется (вызывается virtual ~IReadStrategy()),
    // поэтому delete вручную писать не нужно и утечки невозможны.
    //
    // Тип указателя — базовый IReadStrategy, а лежит в нём объект наследника.
    // Это и делает возможным динамический полиморфизм: strategy->read(path)
    // вызывает реализацию того класса, который сейчас находится в указателе.
    std::unique_ptr<reader::IReadStrategy> strategy;

    // Уже обработанные файлы: содержимое файла → имя стратегии, которой он прочитан.
    // Третий шаблонный параметр — наш хэшер (см. file_content.hpp); четвёртый,
    // KeyEqual, остаётся по умолчанию: std::equal_to → FileContent::operator==.
    std::unordered_map<reader::FileContent, std::string, reader::FileContentHasher> processed;

    bool allOk = true;

    for (int i = 1; i < argc; ++i) {
        const std::string path = argv[i];

        strategy = reader::makeReadStrategy(path);

        if (!strategy) {
            std::cerr << "пропускаю " << path << ": неизвестное расширение файла\n";
            allOk = false;
            continue;
        }

        std::cout << "==== " << path << "  [" << strategy->name() << "] ====\n";

        // Ошибка в одном файле не должна прерывать обработку остальных,
        // поэтому ловим исключение здесь, внутри цикла.
        try {
            reader::FileContent content = reader::FileContent::fromFile(path);

            // find вызывает FileContentHasher, чтобы выбрать корзину,
            // и operator==, чтобы найти ключ внутри неё.
            const auto it = processed.find(content);
            if (it != processed.end()) {
                std::cout << "уже выведен выше (" << it->second << "), пропускаю\n\n";
                continue;
            }

            strategy->read(path);
            processed.emplace(std::move(content), strategy->name());
        } catch (const std::exception& e) {
            std::cerr << "ошибка чтения " << path << ": " << e.what() << "\n";
            allOk = false;
        }

        std::cout << "\n";
    }

    // Код возврата 0 — успех, ненулевой — что-то пошло не так.
    // Так принято в Unix: по этому коду скрипты понимают, упала ли программа.
    return allOk ? 0 : 1;
}
