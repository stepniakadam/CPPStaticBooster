/*
 * Lexer.cpp
 *
 *  Created on: Jan 15, 2023
 *      Author: Adam Stepniak
 */

#include "Lexer.hpp"
#include "CharInfo.hpp"

namespace lexer {
Lexer::Lexer(std::string_view buffer) : buffer(buffer) {
	while (true) {
		skipVertialWhitespaces();

		if (!macroStarted && !isMacroBegin()) {
			skipToNextLine();
			if (processedBuffer()) {
				break;
			}
			continue;
		}
		skipVertialWhitespaces();

		if (!macroStarted) {
			macroStarted = true;
			auto macroToken = readMacro();
			if (hasArguments(macroToken)) {
	//			auto argument = readArgument();
			}
		}

		if (processedBuffer()) {
			break;
		}
	}
}

std::vector<Token> Lexer::getTokens() {
	return {Token{}, Token{}, Token{}};
}

int32_t Lexer::getLineCount() {
	return 0;
}

void Lexer::skipVertialWhitespaces() {
	if (currIdx > buffer.size()) {
		return;
	}

	while (character::isVerticalWhitespace(buffer[currIdx])) {
		currIdx++;
		if (currIdx > buffer.size()) {
			break;
		}
	}
}

void Lexer::startNewLine() {

}

bool Lexer::isMacroBegin() {
	if (buffer[currIdx] == '#') {
		return true;
	}
	return false;
}

void Lexer::skipToNextLine() {
	if (currIdx > buffer.size()) {
		return;
	}

	while (!character::isHorizontalWhitespace(buffer[currIdx])) {
		currIdx++;
		if (currIdx > buffer.size()) {
			break;
		}
	}
}

Token Lexer::readMacro() {
	Token token;
	token.startIdx = currIdx - 1;
	while (character::isLetter(buffer[currIdx])) {
		currIdx++;
	}
	token.endIdx = currIdx;
	return token;
}

bool Lexer::hasArguments(const Token& token) {
	return false;
}

bool Lexer::processedBuffer() {
	return currIdx > buffer.size();
}
} // lexer



