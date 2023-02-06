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
#include <string>

namespace lexer {
enum class TokenType : uint8_t {
	Include,
	IfDef,
	Define,
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
	bool valid{false};
};

extern std::vector<std::string> FORBIDDEN_IDENTIFIERS;

class Lexer {
public:
	Lexer(std::string_view buffer);

	std::vector<Token> getTokens();
	int32_t getLineCount();
private:
	bool skipHorizontalWhitespaces();
	bool skipToNextLine();
	void startNewLine();
	bool isMacroBegin();
	Token readPreprocessorDirective();
	bool handleToken(const Token& token);
	bool processedBuffer();
	bool lineEnds();
	TokenType getTokenType(const Token& token);

	std::string_view buffer;
	int64_t currIdx{};
	std::vector<Token> tokens;
	bool macroStarted{};
};
} // lexer
