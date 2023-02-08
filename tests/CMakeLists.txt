cmake_minimum_required(VERSION 2.8.12)
project(CPPStaticBooster)

add_executable(LexerTests 
	../Lexer.cpp
	../CharInfo.cpp
	LexerTest.cpp)

target_link_libraries(
  LexerTests
  ${CONAN_LIBS_GTEST}
)

add_test(NAME LexerTests COMMAND LexerTests)