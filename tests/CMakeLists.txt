add_executable(image-processor-tests
    test_example.cpp
)

target_link_libraries(image-processor-tests
    PRIVATE
    gtest
    gtest_main
)

target_compile_options(image-processor-tests PRIVATE -Wall -Wextra -pedantic)

add_test(NAME image-processor-tests COMMAND image-processor-tests)
