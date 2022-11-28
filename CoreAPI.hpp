/*
 * CoreAPI.hpp
 *
 *  Created on: Nov 28, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <vector>
#include <string>

namespace core {
class CPPUnit;

class Header {
public:
	std::string getPath();
	std::vector<std::string> getIncludeNames();
	std::vector<Header*> getIncludeHeaders();
	std::vector<CPPUnit*> getConsumers();
	std::size_t getLinesCount();
};

class CPPUnit {
public:
	std::string getPath();
	std::vector<std::string> getIncludeNames();
	std::vector<Header*> getIncludeHeaders();
	std::size_t getLinesCount();
};

class IndexStorage {
public:
	IndexStorage(const std::string& content);

	const Header* getHeaderByPath(const std::string& path);
	std::vector<Header*> getHeadersGT(std::size_t linesCount);
	std::vector<Header*> getHeadersConsumedGT(std::size_t consumersCount);

	const CPPUnit* getCPPUnitByPath(const std::string& path);
	std::vector<CPPUnit*> getCPPUnitGT(std::size_t linesCount);
};
}  // namespace core

