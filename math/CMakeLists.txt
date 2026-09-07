# Создаём статическую библиотеку из трёх .cpp файлов.
# STATIC означает, что код будет скомпилирован в один .a файл и слинкован в исполняемый файл.
add_library(math STATIC
    src/multiply.cpp
    src/power.cpp
    src/divide.cpp
)

# Указываем, где лежат заголовочные файлы для этой библиотеки.
#
# SYSTEM  — добавляет путь как системный (#include <...> работает без предупреждений).
# PUBLIC  — заголовки доступны и внутри самой библиотеки, и всем, кто её подключает.
#           Если бы мы написали PRIVATE, заголовки были бы доступны только внутри math.
target_include_directories(math SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
