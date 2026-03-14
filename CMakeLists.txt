cmake_minimum_required(VERSION 3.15)
project(image-processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ENABLE_CMAKE ON)
set(BOOST_INCLUDE_LIBRARIES program_options)

option(WITH_TESTS "Build application with unit tests" OFF)

add_subdirectory(third_party/boost)

add_executable(image-processor
    src/bmp_factories/bmp_factory.cpp
    main.cpp
)

target_link_libraries(image-processor Boost::program_options)
target_include_directories(image-processor PUBLIC include)

if (WITH_TESTS)
    enable_testing()
    add_subdirectory(third_party/gtest)
    add_subdirectory(tests)
endif()