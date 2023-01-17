/*
 * CMakeCommandsParserTest.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <gtest/gtest.h>

#include <string>

#include "../Lexer.hpp"

class DirectiveGrammarTest : public ::testing::Test {
public:
	void assertIncludeIsAsExpected(lexer::Lexer& lexer) {
		auto tokens = lexer.getTokens();
		EXPECT_EQ(2, tokens.size());
		EXPECT_EQ(lexer::TokenType::Include, tokens[0].type);
		EXPECT_EQ(lexer::TokenType::MacroParam, tokens[1].type);
	}
};

TEST_F(DirectiveGrammarTest, NumberSignShouldBeFirstNonwhiteCharacter_1) {
	lexer::Lexer lexer("#include <string>");
	assertIncludeIsAsExpected(lexer);
}

TEST_F(DirectiveGrammarTest, NumberSignShouldBeFirstNonwhiteCharacter_2) {
	lexer::Lexer lexer("  #include < string>");
	assertIncludeIsAsExpected(lexer);
}

TEST_F(DirectiveGrammarTest, ContinuingPerprocessorLinesAfterBackslash) {
	lexer::Lexer lexer("#   include \\\n< string>");
	assertIncludeIsAsExpected(lexer);
}

TEST(IdentifierGrammarTest, UnicodeIdentifiersShouldBeAllowed_1) {
	lexer::Lexer lexer("#define sól");

	auto tokens = lexer.getTokens();
	ASSERT_EQ(2, tokens.size());
	EXPECT_EQ(8, tokens[1].startIdx);
	EXPECT_EQ(11, tokens[1].endIdx);
}

TEST(IdentifierGrammarTest, UnicodeIdentifiersShouldBeAllowed_2) {
	lexer::Lexer lexer("#define sólóóóó");

	auto tokens = lexer.getTokens();
	ASSERT_EQ(2, tokens.size());
	EXPECT_EQ(8, tokens[1].startIdx);
	EXPECT_EQ(15, tokens[1].endIdx);
}

TEST(IdentifierGrammarTest, UnderscoreIdentifiersShouldBeAllowed) {
	lexer::Lexer lexer("#define _t");

	auto tokens = lexer.getTokens();
	ASSERT_EQ(2, tokens.size());
	EXPECT_EQ(8, tokens[1].startIdx);
	EXPECT_EQ(10, tokens[1].endIdx);
}

TEST(IdentifierGrammarTest, NumberInIdentifierShouldBeAllowed_1) {
	lexer::Lexer lexer("#define _1");

	auto tokens = lexer.getTokens();
	ASSERT_EQ(2, tokens.size());
	EXPECT_EQ(8, tokens[1].startIdx);
	EXPECT_EQ(10, tokens[1].endIdx);
}

TEST(IdentifierGrammarTest, StartingNumberInIdentifierShouldNotBeAllowed) {
	try {
		lexer::Lexer lexer("#define 1test");
		auto tokens = lexer.getTokens();
		FAIL() << "No exception was thrown on incorrect syntax";
	} catch (std::invalid_argument&) { }
}

//
//TEST(LexerTest, WhenIncludeIsCorrectThenReturnsCorrectResult_2) {
//	auto name = getIncludeName("   #include    <string>");
//	EXPECT_EQ("string", name);
//}
//
//TEST(LexerTest, WhenIncludeIsCorrectThenReturnsCorrectResult_3) {
//	auto name = getIncludeName("	#include	<string>  // comment");
//	EXPECT_EQ("string", name);
//}
//
//TEST(LexerTest, WhenIncludeIsCorrectThenReturnsCorrectResult_4) {
//	auto name = getIncludeName("#include \"string\"  // comment");
//	EXPECT_EQ("string", name);
//}
//
//TEST(LexerTest, WhenIncludeIsMalformedThenReturnsEmptyString_1) {
//	auto name = getIncludeName("#include string\"  // comment");
//	EXPECT_EQ("", name);
//}
//
//TEST(LexerTest, WhenIncludeIsMalformedThenReturnsEmptyString_2) {
//	auto name = getIncludeName("#inclu de \"string\"  // comment");
//	EXPECT_EQ("", name);
//}
//
//TEST(LexerTest, WhenIncludeIsMalformedThenReturnsEmptyString_3) {
//	auto name = getIncludeName("#test123 \"string\"  // comment");
//	EXPECT_EQ("", name);
//}
//
//TEST(LexerTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_1) {
//	auto tokens = getTokens("#include ");
//	ASSERT_EQ(1, tokens.size());
//	EXPECT_EQ(TokenType::Include, tokens[0].type);
//}
//
//TEST(LexerTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_2) {
//	auto tokens = getTokens("#ifndef abc");
//	ASSERT_EQ(1, tokens.size());
//	EXPECT_EQ(TokenType::IfNDef, tokens[0].type);
//}
//
//TEST(LexerTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_3) {
//	auto tokens = getTokens("#if defined abc");
//	ASSERT_EQ(1, tokens.size());
//	EXPECT_EQ(TokenType::IfDefined, tokens[0].type);
//}
//
//TEST(LexerTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_4) {
//	auto tokens = getTokens(" #pragma once ");
//	ASSERT_EQ(1, tokens.size());
//	EXPECT_EQ(TokenType::PragmaOnce, tokens[0].type);
//}
//
//TEST(LexerTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_5) {
//	auto tokens = getTokens("    int main() {");
//	EXPECT_EQ(0, tokens.size());
//}
//
//TEST(LexerTest, WhenTokenExistsThenThenShouldBeReturnedCorretly_6) {
//	auto file1 = R"(#pragma once
//#include abc
//
//int main () {
//return 0;
//})";
//
//	auto tokens = getTokens(file1);
//	ASSERT_EQ(2, tokens.size());
//
//	EXPECT_EQ(TokenType::PragmaOnce, tokens[0].type);
//	EXPECT_EQ(0, tokens[0].startIdx);
//	EXPECT_EQ(12, tokens[0].endIdx);
//
//	EXPECT_EQ(TokenType::Include, tokens[1].type);
//	EXPECT_EQ(13, tokens[1].startIdx);
//	EXPECT_EQ(21, tokens[1].endIdx);
//}
