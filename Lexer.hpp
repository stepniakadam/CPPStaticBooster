/*
 * Lexer.hpp
 *
 *  Created on: Jan 15, 2023
 *      Author: Adam Stepniak
 */

#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace lexer {
enum class TokenType : uint8_t {
	Include,
	Define,
	IfDef,
	IfNDef,
	IfDefined,
	IfNDefined,
	Else,
	Elif,
	Endif,
	MacroParam,
	Unknown
};

struct Token {
	TokenType type{TokenType::Unknown};
	int64_t startIdx{-1};
	int64_t endIdx{-1};
};

class Lexer {
public:
	Lexer(std::string_view buffer);

	std::vector<Token> getTokens();
	int32_t getLineCount();
private:
	void skipVertialWhitespaces();
	void startNewLine();
	bool isMacroBegin();
	void skipToNextLine();
	Token readMacro();
	bool hasArguments(const Token& token);
	bool processedBuffer();

	std::string_view buffer;
	int64_t currIdx{};
	std::vector<Token> tokens;
	bool macroStarted{};
};
} // lexer
