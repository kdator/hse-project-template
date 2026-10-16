# ======================================================================================
#  Makefile — тонкая обёртка над CMake, чтобы не вспоминать длинные команды.
#
#  Сам он ничего не компилирует: каждая цель просто вызывает cmake, который
#  генерирует настоящую систему сборки и запускает её.
#
#  У каждой цели СВОЯ папка сборки, и это не прихоть: папка сборки содержит
#  кэш CMake (CMakeCache.txt) с путём к исходникам и всеми настройками, поэтому
#  в одну папку нельзя конфигурировать два разных проекта. Заодно примеры
#  становятся независимыми: build-math не требует интернета и не собирает
#  сторонние библиотеки.
#
#      build/            ← сборка всего репозитория из корневого CMakeLists.txt
#      build-math/       ← сборка только math-example
#      build-strategy/   ← сборка только strategy-example
#
#      make build-math               собрать пример math-example
#      make build-strategy-example   собрать пример strategy-example
#      make build-all                собрать всё из корня (через ./CMakeLists.txt)
#      make run-math                 собрать и запустить demo
#      make run-strategy-example     собрать и запустить filereader на тестовых данных
#      make clean                    удалить все папки сборки
# ======================================================================================

CMAKE ?= cmake
JOBS  ?= $(shell nproc 2>/dev/null || echo 4)

BUILD_ALL      := build
BUILD_MATH     := build-math
BUILD_STRATEGY := build-strategy

# .PHONY перечисляет цели, которые не создают файла с таким именем.
# Без этого make решил бы, что цель build-math уже «готова», если рядом
# случайно появится файл с именем build-math.
.PHONY: all build-math build-strategy-example build-all run-math run-strategy-example clean

# Цель по умолчанию: просто `make` соберёт оба примера.
all: build-math build-strategy-example

# --------------------------------------------------------------------------------------
#  Пример 1: math-example
# --------------------------------------------------------------------------------------
# Первая команда (configure) читает CMakeLists.txt и генерирует систему сборки,
# вторая (build) запускает её. Повторный configure безвреден: CMake видит готовый
# кэш в папке сборки и просто проверяет, не изменились ли CMakeLists.txt.
build-math:
	$(CMAKE) -S math-example -B $(BUILD_MATH)
	$(CMAKE) --build $(BUILD_MATH) -j $(JOBS)

# --------------------------------------------------------------------------------------
#  Пример 2: strategy-example
# --------------------------------------------------------------------------------------
# Первый запуск небыстрый: CMake скачает nlohmann/json и OpenXLSX (нужен интернет)
# и соберёт OpenXLSX вместе с её зависимостями miniz и pugixml.
# Дальше скачанное лежит в $(BUILD_STRATEGY)/_deps и переиспользуется.
build-strategy-example:
	$(CMAKE) -S strategy-example -B $(BUILD_STRATEGY)
	$(CMAKE) --build $(BUILD_STRATEGY) -j $(JOBS)

# --------------------------------------------------------------------------------------
#  Оба примера одной сборкой через корневой CMakeLists.txt
# --------------------------------------------------------------------------------------
build-all:
	$(CMAKE) -S . -B $(BUILD_ALL)
	$(CMAKE) --build $(BUILD_ALL) -j $(JOBS)

# --------------------------------------------------------------------------------------
#  Запуск
# --------------------------------------------------------------------------------------
# Запись `run-math: build-math` означает зависимость: перед запуском make
# обязательно выполнит сборку.
run-math: build-math
	$(BUILD_MATH)/bin/demo

run-strategy-example: build-strategy-example
	$(BUILD_STRATEGY)/bin/filereader \
		strategy-example/data/employees.xlsx \
		strategy-example/data/config.json

clean:
	rm -rf $(BUILD_ALL) $(BUILD_MATH) $(BUILD_STRATEGY)
