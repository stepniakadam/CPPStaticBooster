/*
 * CMakeCommandsParser.hpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <string>
#include <vector>

namespace parser {
struct TranslationUnit {
	std::string path;
	std::vector<std::string> includePaths;
	auto operator<=>(const TranslationUnit&) const = default;
};

class CMakeCommandsParser {
public:
	std::vector<TranslationUnit> getTranslationUnits(const std::string& path);
};
}  // namespace parser
