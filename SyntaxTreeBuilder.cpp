/*
 * CoreAPI.cpp
 *
 *  Created on: Nov 28, 2022
 *      Author: Adam Stepniak
 */

#include "SyntaxTreeBuilder.hpp"
#include "Utilities.hpp"

namespace core {

SyntaxTreeBuilder::SyntaxTreeBuilder(const std::vector<parser::TranslationUnit>& tUnits,
		FileReaderInterface* fileReader) {
	build(tUnits, fileReader);
}

void SyntaxTreeBuilder::build(const std::vector<parser::TranslationUnit>& tUnits,
		FileReaderInterface* fileReader) {
	for (const auto& t : tUnits) {
		auto cppUnit = std::make_unique<CPPUnit>();
		cppUnit->path = t.path;

		fileReader->open(t.path);
		while (fileReader->isNextLineAvailable()) {
			auto line = fileReader->readLine();
			auto incl = getIncludeName(line);
			if (!incl.empty()) {
				auto headerUnit = std::make_unique<HeaderUnit>();
				// TODO
			}
		}
	}

}

const HeaderUnit* SyntaxTreeBuilder::getHeaderUnit(const std::string& path) {
	return {};
}

const CPPUnit* SyntaxTreeBuilder::getCPPUnit(const std::string& path) {
	return {};
}
}  // namespace core



