cmake_minimum_required(VERSION 2.8.12)
project(CPPStaticBooster)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions("-std=c++20")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(CPPStaticBooster 
	CMakeCommandsParser.cpp
	SyntaxTreeBuilder.cpp
	CharInfo.cpp
	Lexer.cpp
	main.cpp)
	
target_link_libraries(CPPStaticBooster 
	${CONAN_LIBS})

# Unit tests
enable_testing()

add_executable(UnitTests 
	CMakeCommandsParser.cpp 
	SyntaxTreeBuilder.cpp
	Lexer.cpp
	CharInfo.cpp
	tests/CMakeCommandsParserTest.cpp
	tests/LexerTest.cpp
	tests/SyntaxTreeBuilderTest.cpp)

target_link_libraries(
  UnitTests
  ${CONAN_LIBS}
)
