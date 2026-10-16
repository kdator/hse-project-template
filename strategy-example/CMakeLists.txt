# ======================================================================================
#  Пример 2: сторонние зависимости + паттерн Strategy
#  Цель filereader: читает .json и .xlsx файлы, переданные в аргументах, и печатает их.
# ======================================================================================
#  Этот файл самодостаточен: папку можно собрать как отдельный проект
#      cmake -S strategy-example -B build/strategy-example
#      cmake --build build/strategy-example
#  либо из корня репозитория через add_subdirectory (см. ../CMakeLists.txt).
# ======================================================================================

# FetchContent появился в CMake 3.11 (FetchContent_MakeAvailable — в 3.14),
# а сама библиотека OpenXLSX требует не меньше 3.15.
cmake_minimum_required(VERSION 3.16)

project(StrategyExample CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исполняемый файл окажется в <папка сборки>/bin/filereader.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ======================================================================================
#  Часть 1. Сторонние библиотеки
# ======================================================================================
# Вынесены в отдельный файл, чтобы этот CMakeLists.txt оставался читаемым.
# include() просто выполняет команды из файла в ТЕКУЩЕЙ области видимости
# (в отличие от add_subdirectory, который создаёт дочернюю область).
# После этого доступны цели nlohmann_json::nlohmann_json и OpenXLSX::OpenXLSX.
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Dependencies.cmake)

# ======================================================================================
#  Часть 2. INTERFACE-библиотека с общими флагами компиляции
# ======================================================================================
# INTERFACE-библиотека не содержит ни одного .cpp файла и ничего не компилирует.
# Это «пустая цель», которая только хранит требования и передаёт их всем,
# кто с ней слинковался. Удобный способ не дублировать флаги в каждой цели.
#
# Важно, что флаги предупреждений применяются только к НАШИМ целям: чужой код
# из FetchContent собирается со своими настройками, и мы не тонем в предупреждениях
# из чужих заголовков.
add_library(project_warnings INTERFACE)

if(MSVC)
    target_compile_options(project_warnings INTERFACE /W4)
else()
    target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

# ======================================================================================
#  Часть 3. Библиотека стратегий и CLI
# ======================================================================================
# Библиотека reader объявлена в reader/CMakeLists.txt. Она должна быть подключена
# ПОСЛЕ include(Dependencies.cmake) и после создания project_warnings:
# на момент выполнения target_link_libraries(reader ...) все эти цели уже должны
# существовать.
add_subdirectory(reader)

add_executable(filereader app/main.cpp)

# PRIVATE: filereader — исполняемый файл, с ним никто не линкуется,
# поэтому «протекать» зависимостям некуда, и PUBLIC здесь был бы бессмысленным.
#
# Транзитивность в действии: мы линкуем только reader, но в итоговый filereader
# попадёт и код OpenXLSX с miniz и pugixml — CMake сам протащит их по графу
# зависимостей. При этом заголовки этих библиотек filereader НЕ видит,
# так как в reader они подключены как PRIVATE.
target_link_libraries(filereader PRIVATE reader project_warnings)
