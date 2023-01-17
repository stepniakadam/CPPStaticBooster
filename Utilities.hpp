/*
 * Utilities.hpp
 *
 *  Created on: Dec 3, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <string>
#include <vector>

namespace {
std::string getIncludeName(const std::string& line) {
	std::string basicInclude("#include");
	if (line.size() < basicInclude.size()) {
		return "";
	}

	std::string inclPath;
	bool hashFound{false};
	bool inclFound{false};

	for (int idx = 0; idx < line.size(); ++idx) {
		if (!hashFound && line[idx] == '#') {
			hashFound = true;
		} else if (hashFound && line[idx] == 'i') {
			auto left = line.size() - idx;
			if (basicInclude.size() - 1 > left) {
				continue;
			}

			for (int j = 2; j < basicInclude.size(); ++j) {
				if (line[++idx] != basicInclude[j]) {
					break;
				}
			}

			inclFound = true;
		} else if (inclFound && (line[idx] == '<' || line[idx] == '"')) {
			idx++;
			while (line[idx] != '>' && line[idx] != '"') {
				inclPath.push_back(line[idx]);
				idx++;
			}
		} else if (line[idx] == ' ' || line[idx] == '\t') {
			continue;
		} else {
			break;
		}
	}

	return inclPath;
}

enum class TokenType {
	Include,
	PragmaOnce,
	Define,
	IfDef,
	IfNDef,
	IfDefined,
	IfNDefined,
	Unknown
};

std::vector<std::pair<TokenType, std::string>> tokens {
	{TokenType::Include, {"#include"}},
	{TokenType::PragmaOnce, {"#pragma once"}},
	{TokenType::Define, {"#define"}},
	{TokenType::IfDef, {"#ifdef"}},
	{TokenType::IfNDef, {"#ifndef"}},
	{TokenType::IfDefined, {"#if defined"}},
	{TokenType::IfNDefined, {"#if !defined"}}
};


std::vector<Token> getTokens(std::string_view line) {
	std::vector<Token> tPositions;

	int tCharIdx = 0;
	int tokenIdx = 0;
	Token tPos;

	for (int cIdx = 0; cIdx < line.size(); ++cIdx) {
		char c = line[cIdx];

		if (tPos.startIdx == -1) {
			while (tokenIdx < tokens.size()) {
				auto& token = tokens[tokenIdx].second;

				if (line[cIdx] == token[tCharIdx]) {
					tPos.startIdx = cIdx;
					tCharIdx++;
					break;
				}
				tokenIdx++;
			}
			if (tPos.startIdx == -1) {
				tokenIdx = 0;
			}
		} else {
			auto& token = tokens[tokenIdx].second;

			if (tCharIdx >= token.size()) {
				tPos.endIdx = cIdx;
				tPos.type = tokens[tokenIdx].first;
				tPositions.push_back(tPos);

				tPos = Token{};
				tCharIdx = 0;
				tokenIdx = 0;
			} else if (line[cIdx] != token[tCharIdx]) {
				cIdx = tPos.startIdx - 1;
				tPos = Token{};
				tCharIdx = 0;
				tokenIdx++;
			} else {
				tCharIdx++;
			}
		}
	}

	return tPositions;
}
}  // namespace

