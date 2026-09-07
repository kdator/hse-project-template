# Минимальная версия CMake, с которой совместим этот файл.
# Гарантирует, что студент не соберёт проект слишком старым инструментом.
cmake_minimum_required(VERSION 3.10)

# Объявляем проект: его имя и язык.
# CMake использует это имя для генерации файлов IDE и отображения в логах.
project(MathDemo CXX)

# Устанавливаем стандарт C++.
# CMAKE_CXX_STANDARD_REQUIRED запрещает "молча откатиться" на более старый стандарт.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем подпапку math/.
# CMake войдёт в неё, прочитает её CMakeLists.txt и выполнит все команды оттуда.
# После этого цель (target) с именем "math" становится доступна в этом файле.
add_subdirectory(math)

# Создаём исполняемый файл demo из одного исходника.
add_executable(demo main.cpp)

# Линкуем исполняемый файл с библиотекой math.
# Благодаря PUBLIC в target_include_directories внутри math/CMakeLists.txt
# директория math/include/ автоматически добавляется в пути поиска заголовков demo,
# поэтому в main.cpp можно писать #include <multiply.h> без дополнительных настроек.
target_link_libraries(demo PRIVATE math)
