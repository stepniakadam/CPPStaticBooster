/*
 * CoreAPI.cpp
 *
 *  Created on: Nov 28, 2022
 *      Author: Adam Stepniak
 */

#include "CoreAPI.hpp"

namespace core {

std::string Header::getPath() {
	return {};
}

std::vector<std::string> Header::getIncludeNames() {
	return {};
}

std::vector<Header*> Header::getIncludeHeaders() {
	return {};
}

std::vector<CPPUnit*> Header::getConsumers() {
	return {};
}

std::size_t Header::getLinesCount() {
	return {};
}

std::string CPPUnit::getPath() {
	return {};
}

std::vector<std::string> CPPUnit::getIncludeNames() {
	return {};
}

std::vector<Header*> CPPUnit::getIncludeHeaders() {
	return {};
}

std::size_t CPPUnit::getLinesCount() {
	return {};
}

IndexStorage::IndexStorage(const std::string& content) {
}

const Header* IndexStorage::getHeaderByPath(const std::string& path) {
	return {};
}

std::vector<Header*> IndexStorage::getHeadersGT(std::size_t linesCount) {
	return {};
}

std::vector<Header*> IndexStorage::getHeadersConsumedGT(std::size_t consumersCount) {
	return {};
}

const CPPUnit* IndexStorage::getCPPUnitByPath(const std::string& path) {
	return {};
}

std::vector<CPPUnit*> IndexStorage::getCPPUnitGT(std::size_t linesCount) {
	return {};
}
}  // namespace core



