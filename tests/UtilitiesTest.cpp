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
