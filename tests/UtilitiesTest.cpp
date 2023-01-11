/*
 * CMakeCommandsParserTest.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <gtest/gtest.h>

#include <string>

#include "../Utilities.hpp"

TEST(UtilitiesTest, WhenIncludeIsCorrectThenReturnsCorrectResult_1) {
	auto name = getIncludeName("#include <string>");
	EXPECT_EQ("string", name);
}

TEST(UtilitiesTest, WhenIncludeIsCorrectThenReturnsCorrectResult_2) {
	auto name = getIncludeName("   #include    <string>");
	EXPECT_EQ("string", name);
}

TEST(UtilitiesTest, WhenIncludeIsCorrectThenReturnsCorrectResult_3) {
	auto name = getIncludeName("	#include	<string>  // comment");
	EXPECT_EQ("string", name);
}

TEST(UtilitiesTest, WhenIncludeIsCorrectThenReturnsCorrectResult_4) {
	auto name = getIncludeName("#include \"string\"  // comment");
	EXPECT_EQ("string", name);
}

TEST(UtilitiesTest, WhenIncludeIsMalformedThenReturnsEmptyString_1) {
	auto name = getIncludeName("#include string\"  // comment");
	EXPECT_EQ("", name);
}

TEST(UtilitiesTest, WhenIncludeIsMalformedThenReturnsEmptyString_2) {
	auto name = getIncludeName("#inclu de \"string\"  // comment");
	EXPECT_EQ("", name);
}

TEST(UtilitiesTest, WhenIncludeIsMalformedThenReturnsEmptyString_3) {
	auto name = getIncludeName("#test123 \"string\"  // comment");
	EXPECT_EQ("", name);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_1) {
	auto name = getToken("#include");
	EXPECT_EQ("#include", name);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_2) {
	auto name = getToken("#ifndef abc");
	EXPECT_EQ("#ifndef", name);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_3) {
	auto name = getToken("#if defined abc");
	EXPECT_EQ("#if defined", name);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_4) {
	auto name = getToken("    #pragma  once");
	EXPECT_EQ("#pragma once", name);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_5) {
	auto name = getToken("    int main() {");
	EXPECT_EQ("", name);
}
