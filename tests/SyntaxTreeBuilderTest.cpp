/*
 * CMakeCommandsParserTest.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <gtest/gtest.h>

#include <string>

#include "../SyntaxTreeBuilder.hpp"

using namespace core;

std::string custom2 = R"(
#include <string>
#include <vector>
)";

std::string custom1 = R"(
#include <string>
#include <vector>
)";



// Demonstrate some basic assertions.
TEST(SyntaxTreeBuilderTest, WhenHeaderIsParsedThenResultIsAsExpected) {
//	std::vector<parser::TranslationUnit> units;
//
//	parser::TranslationUnit tu1;
//	tu1.path = "/tmp/cppUnit1.cpp";
//	tu1.includePaths = "/tmp/inc/";
//	units.push_back(tu1);
//
////	SyntaxTreeBuilder syntaxTree(units, );
//	auto unit = syntaxTree.getCPPUnit("/tmp/cppUnit1.cpp");
//	EXPECT_EQ(3, unit->includeHeaders.size());
}



