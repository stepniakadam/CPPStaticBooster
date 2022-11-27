cmake_minimum_required(VERSION 2.8.12)
project(codeAccelerator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(codeAccelerator main.cpp)
target_link_libraries(codeAccelerator ${CONAN_LIBS})
