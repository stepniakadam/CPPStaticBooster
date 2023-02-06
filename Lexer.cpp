/*
 * Lexer.cpp
 *
 *  Created on: Jan 15, 2023
 *      Author: Adam Stepniak
 */

#include "Lexer.hpp"
#include "CharInfo.hpp"

namespace lexer {
// Identifiers not allowed according to:
// https://gcc.gnu.org/onlinedocs/cpp/Tokenization.html
std::vector<std::string> FORBIDDEN_IDENTIFIERS {
	"and_eq",
	"bitand",
	"define",
	"and",
	"bitor",
	"compl",
	"not",
	"not_eq",
	"or",
	"or_eq",
	"xor",
	"xor_eq"
};

Lexer::Lexer(std::string_view buffer) : buffer(buffer) {
	while (!processedBuffer()) {
		if (!skipHorizontalWhitespaces()) {
			break;
		}

		if (!macroStarted && !isMacroBegin()) {
			if (!skipToNextLine()) {
				break;
			}

			continue;
		}
		currIdx++;
		if (currIdx > buffer.size()) {
			break;
		}

		// It is allowed to have whitespace
		// between # and any preprocessor directive
		if (!skipHorizontalWhitespaces()) {
			break;
		}

		auto token = readPreprocessorDirective();
		tokens.push_back(token);
		if (handleToken(token)) {
			return;
		}
	}
}

std::vector<Token> Lexer::getTokens() {
	return tokens;
}

int32_t Lexer::getLineCount() {
	return 0;
}

bool Lexer::skipHorizontalWhitespaces() {
	while (character::isHorizontalWhitespace(buffer[currIdx])) {
		currIdx++;
		if (currIdx > buffer.size()) {
			return false;
		}
	}

	return true;
}

bool Lexer::skipToNextLine() {
	while (!character::isVerticalWhitespace(buffer[currIdx])) {
		currIdx++;
		if (currIdx > buffer.size()) {
			return false;
		}
	}
	return true;
}

void Lexer::startNewLine() {

}

bool Lexer::isMacroBegin() {
	if (buffer[currIdx] == '#') {
		return true;
	}
	return false;
}

Token Lexer::readPreprocessorDirective() {
	Token token;
	token.startIdx = currIdx;
	while (character::isLetter(buffer[currIdx])) {
		currIdx++;
	}
	token.endIdx = currIdx;
	token.type = getTokenType(token);

	return token;
}

bool Lexer::handleToken(const Token& token) {
	if (token.type == TokenType::Include) {
		tokens.emplace_back(Token{});
		auto& token = tokens.back();
		token.startIdx = currIdx;
		token.type = TokenType::MacroParam;

		if (!skipHorizontalWhitespaces()) {
			return false;
		}
		while (character::isVerticalWhitespace(buffer[currIdx]) || buffer[currIdx] == '\\') {
			currIdx++;
			if (currIdx > buffer.size()) {
				return false;
			}
		}

		if (buffer[currIdx] != '<' && buffer[currIdx] != '\\') {
			return false;
		}
		currIdx++;
		if (currIdx >= buffer.size()) {
			return false;
		}

		while (character::isAlphanumeric(buffer[currIdx])) {
			currIdx++;
			if (currIdx > buffer.size()) {
				return false;
			}
		}

		if (buffer[currIdx] != '>') {
			return false;
		}
		token.endIdx = currIdx;
		token.valid = true;

		return true;
	}
	return false;
}

bool Lexer::processedBuffer() {
	return currIdx > buffer.size();
}

bool Lexer::lineEnds() {
	return false;
}

TokenType Lexer::getTokenType(const Token& token) {
	std::string_view tokenStr(&buffer[token.startIdx], token.endIdx - token.startIdx);

	if (tokenStr == "include") {
		return TokenType::Include;
	}

	return TokenType::Unknown;
}

} // lexer



