/*
 * Utilities.hpp
 *
 *  Created on: Dec 3, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <string>

namespace {
std::string getIncludeName(const std::string& line) {
	constexpr std::string_view basicInclude("#include");
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
}  // namespace

