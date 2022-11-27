/*
 * CMakeCommandsParser.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <string>

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/PrintHandler.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Query.h"

#include "CMakeCommandsParser.hpp"

namespace {
std::vector<std::string> getIncludePathsFromArguments(const Poco::JSON::Array& arguments) {
	std::vector<std::string> paths;

	for (auto& arg : arguments) {
		auto a = arg.toString();

		bool includeWasFound = a.size() > 2 &&
							   a[0] == '-' &&
							   a[1] == 'I';
		if (includeWasFound) {
			paths.emplace_back(a.substr(2, a.size() - 2));
		}
	}

	return paths;
}

std::vector<std::string> getIncludePathsFromCommand(const std::string& command) {
	std::vector<std::string> paths;

	constexpr int beginNotFound = -1;
	int beginPos = beginNotFound;
	bool includeWasFound{false};

	for (int idx = 0; idx < command.size(); ++idx) {
		if (!includeWasFound) {
			includeWasFound = beginPos == -1 &&
							  idx - 1 > 0 &&
							  command[idx - 1] == '-' &&
							  command[idx] == 'I';

			if (includeWasFound) {
				continue;
			}
		} else if (beginPos == beginNotFound) {
			if (command[idx] != ' ') {
				beginPos = idx;
			}
		} else {
			bool endWasFound = command[idx] == ' ';
			if (endWasFound) {
				paths.emplace_back(command.substr(beginPos, idx - beginPos));
				beginPos = beginNotFound;
				includeWasFound = false;
			}
		}
	}

	return paths;
}
}  // namespace

std::vector<TranslationUnit> CMakeCommandsParser::getTranslationUnits(const std::string& compileCommands) {
	std::vector<TranslationUnit> units;

	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(compileCommands);

	auto root = result.extract<Poco::JSON::Array::Ptr>();
	for (auto el : *root) {
		const auto& entry = el.extract<Poco::JSON::Object::Ptr>();

		const auto& file = entry->get("file");
		const auto& command = entry->get("command");
		const auto& arguments = entry->get("arguments");

		bool isValid = (!file.isEmpty() && file.isString()) &&
					   ((!command.isEmpty() && command.isString()) ||
					   (!arguments.isEmpty() && arguments.isArray()));

		if (!isValid) {
			std::stringstream ss;
			entry->stringify(ss);
			std::string msg = std::string("Incorrect format of entry: \n") + ss.str();
			throw std::invalid_argument(msg);
		}

		TranslationUnit tu;
		tu.path = file.extract<std::string>();

		if (!command.isEmpty()) {
			const auto& commandStr = command.extract<std::string>();
			tu.includePaths = getIncludePathsFromCommand(commandStr);
		} else if (!arguments.isEmpty()) {
			const auto& argumentsPtr = arguments.extract<Poco::JSON::Array::Ptr>();
			tu.includePaths = getIncludePathsFromArguments(*argumentsPtr);
		}

		units.emplace_back(std::move(tu));
	}

	return units;
}

