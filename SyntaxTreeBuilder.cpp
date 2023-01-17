/*
 * CoreAPI.cpp
 *
 *  Created on: Nov 28, 2022
 *      Author: Adam Stepniak
 */

#include <unordered_map>
#include <filesystem>

#include "SyntaxTreeBuilder.hpp"

namespace core {

SyntaxTreeBuilder::SyntaxTreeBuilder(const std::vector<parser::TranslationUnit>& tUnits,
		FileReaderInterface* fileReader, SystemInterface* sysInterface) {
	build(tUnits, fileReader, sysInterface);
}

void SyntaxTreeBuilder::build(const std::vector<parser::TranslationUnit>& tUnits,
		FileReaderInterface* fileReader, SystemInterface* sysInterface) {

	std::unordered_map<std::string, CPPUnit> cppUnits;
	std::unordered_map<std::string, HeaderUnit> headerUnits;

	for (const auto& t : tUnits) {
		auto& cppUnit = cppUnits[t.path];

		fileReader->open(t.path);
		auto content = fileReader->read();


	}
}

const HeaderUnit* SyntaxTreeBuilder::getHeaderUnit(const std::string& path) {
	return {};
}

const CPPUnit* SyntaxTreeBuilder::getCPPUnit(const std::string& path) {
	return {};
}
}  // namespace core



