cmake_minimum_required(VERSION 3.15)
project(image-processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ENABLE_CMAKE ON)
set(BOOST_INCLUDE_LIBRARIES program_options)

add_subdirectory(external/boost)

add_executable(image-processor main.cpp)

target_link_libraries(image-processor Boost::program_options)