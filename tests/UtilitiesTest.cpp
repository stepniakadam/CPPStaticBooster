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
	auto tokens = getTokens("#include ");
	ASSERT_EQ(1, tokens.size());
	EXPECT_EQ(TokenType::Include, tokens[0].type);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_2) {
	auto tokens = getTokens("#ifndef abc");
	ASSERT_EQ(1, tokens.size());
	EXPECT_EQ(TokenType::IfNDef, tokens[0].type);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_3) {
	auto tokens = getTokens("#if defined abc");
	ASSERT_EQ(1, tokens.size());
	EXPECT_EQ(TokenType::IfDefined, tokens[0].type);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_4) {
	auto tokens = getTokens(" #pragma once ");
	ASSERT_EQ(1, tokens.size());
	EXPECT_EQ(TokenType::PragmaOnce, tokens[0].type);
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_5) {
	auto tokens = getTokens("    int main() {");
	EXPECT_EQ(0, tokens.size());
}

TEST(UtilitiesTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_6) {
	auto file1 = R"(#pragma once
#include abc

int main () {
return 0;
})";

	auto tokens = getTokens(file1);
	ASSERT_EQ(2, tokens.size());

	EXPECT_EQ(TokenType::PragmaOnce, tokens[0].type);
	EXPECT_EQ(0, tokens[0].startIdx);
	EXPECT_EQ(12, tokens[0].endIdx);

	EXPECT_EQ(TokenType::Include, tokens[1].type);
	EXPECT_EQ(13, tokens[1].startIdx);
	EXPECT_EQ(21, tokens[1].endIdx);
}
