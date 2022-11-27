/*
 * CMakeCommandsParserTest.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <gtest/gtest.h>

#include <string>

#include "../CMakeCommandsParser.hpp"

std::string compileCommandsRef1 = R"(
[ 
	{
		"directory": "/home/tester/tests/headers_stats/tests",
		"command": "/usr/bin/g++ -I/home/tester/tests/headers_stats/include1 -I/home/tester/tests/headers_stats/include2 -o /home/tester/tests/headers_stats/tests/file1.cpp.o -c /home/tester/tests/headers_stats/tests/file1.cpp",
		"file": "/home/tester/tests//headers_stats/tests/file1.cpp"
	},
	{
		"directory": "/home/tester/tests/headers_stats/tests",
		"arguments": ["/usr/bin/g++",  "-I/home/tester/tests/headers_stats/include3", "-I/home/tester/tests/headers_stats/include4", "-o", "/home/tester/tests//headers_stats/tests/file2.cpp.o", "-c", "/home/tester/tests/headers_stats/tests/file2.cpp"],
		"file": "/home/tester/tests//headers_stats/tests/file2.cpp"
	},
	{
		"directory": "/home/tester/tests//headers_stats/tests",
		"command": "/usr/bin/g++ -I /home/tester/tests/headers_stats/include5 -o /home/tester/tests//headers_stats/tests/file3.cpp.o -c /home/tester/tests/headers_stats/tests/file3.cpp",
		"file": "/home/tester/tests/headers_stats/tests/file3.cpp"
	},
	{
		"directory": "/home/tester/tests//headers_stats/tests",
		"arguments": ["/usr/bin/g++",  "-I/home/tester/tests/headers_stats/include6", "-o", "/home/tester/tests/headers_stats/tests/file4.cpp.o", "-c", "/home/tester/tests/headers_stats/tests/file4.cpp"],
		"file": "/home/tester/tests/headers_stats/tests/file4.cpp"
	}
]
)";

// Demonstrate some basic assertions.
TEST(CMakeCommandParserTest, WhenParsedThenResultAsInRefernceFile) {
	CMakeCommandsParser parser;
	auto tUnits = parser.getTranslationUnits(compileCommandsRef1);

	EXPECT_EQ(4, tUnits.size());

	TranslationUnit expectedTu1 {
		"/home/tester/tests//headers_stats/tests/file1.cpp",
		{"/home/tester/tests/headers_stats/include1",
		 "/home/tester/tests/headers_stats/include2"}
	};
	EXPECT_EQ(expectedTu1, tUnits[0]);

	TranslationUnit expectedTu2 {
		"/home/tester/tests//headers_stats/tests/file2.cpp",
		{"/home/tester/tests/headers_stats/include3",
		 "/home/tester/tests/headers_stats/include4"}
	};
	EXPECT_EQ(expectedTu2, tUnits[1]);

	TranslationUnit expectedTu3 {
		"/home/tester/tests/headers_stats/tests/file3.cpp",
		{"/home/tester/tests/headers_stats/include5"}
	};
	EXPECT_EQ(expectedTu3, tUnits[2]);

	TranslationUnit expectedTu4 {
		"/home/tester/tests/headers_stats/tests/file4.cpp",
		{"/home/tester/tests/headers_stats/include6"}
	};
	EXPECT_EQ(expectedTu4, tUnits[3]);
}



