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

std::string getToken(std::string_view line) {
	static std::vector<std::string> tokens {
		{"#include"},
		{"#pragma once"},
		{"#define"},
		{"#ifdef"},
		{"#ifndef"},
		{"#if defined"},
		{"#if !defined"}
	};

	int tIdx = 0;
	int tCharIdx = 0;
	bool partialMatch{false};
	bool found{false};

	for (int cIdx = 0; cIdx < line.size(); ++cIdx) {
		for (; tIdx < tokens.size(); ++tIdx) {
			if (line[cIdx] == tokens[tIdx][tCharIdx]) {
				tCharIdx++;
				if (tCharIdx >= tokens[tIdx].size()) {
					found = true;
				}
				partialMatch = true;
				break;
			} else if (partialMatch && line[cIdx] == ' ' &&
					tokens[tIdx][tCharIdx - 1] == ' ') {
				break;
			}
		}

		if (!partialMatch) {
			tIdx = 0;
		}
		if (found) {
			break;
		}
	}

	if (found) {
		return tokens[tIdx];
	} else {
		return "";
	}
}
}  // namespace

