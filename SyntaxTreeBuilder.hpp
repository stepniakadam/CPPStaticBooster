/*
 * CoreAPI.hpp
 *
 *  Created on: Nov 28, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <vector>
#include <string>
	#	include <memory>

#include "FileReaderInterace.hpp"
#include "CMakeCommandsParser.hpp"

namespace core {
class CPPUnit;

struct HeaderUnit {
	std::string path;
	std::vector<std::string> includeNames;
	std::vector<HeaderUnit*> includeHeaders;
	std::vector<CPPUnit*> consumers;
	std::size_t lineCount;
};

struct CPPUnit {
	std::string path;
	std::vector<std::string> includeName;
	std::vector<HeaderUnit*> includeHeaders;
	std::size_t lineCount;
};

class SyntaxTreeBuilder {
public:
	SyntaxTreeBuilder(const std::vector<parser::TranslationUnit>& tUnits,
			FileReaderInterface* fileReader);

	const HeaderUnit* getHeaderUnit(const std::string& path);
	const CPPUnit* getCPPUnit(const std::string& path);
private:
	void build(const std::vector<parser::TranslationUnit>& tUnits,
			FileReaderInterface* fileReader);

	std::vector<std::unique_ptr<HeaderUnit>> headerUnits;
	std::vector<std::unique_ptr<CPPUnit>> cppUnits;
};
}  // namespace core

