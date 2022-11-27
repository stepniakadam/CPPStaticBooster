#include <iostream>

#include <string>
#include <fstream>
#include <streambuf>

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/PrintHandler.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Query.h"

std::string getJsonConent(const std::string& path) {
	std::ifstream compileCommands(path);
	std::string json((std::istreambuf_iterator<char>(compileCommands)),
	                  std::istreambuf_iterator<char>());

	return json;
}

struct TranslationUnit {
	std::string path;
	std::vector<std::string> includePaths;
};

std::vector<std::string> getIncludePathsFromArguments(const std::string& arguments) {
	std::vector<std::string> paths;



	return paths;
}

//std::vector<std::string> getIncludePathsFromCommand(const std::string& command) {
//	std::vector<std::string> paths;
//
//	int beginPos = -1;
//
//	for (int idx = 0; idx < paths.size(); ++idx) {
//		if (paths[idx] == '-' &&
//			idx + 1 < paths.size() &&
//			paths[idx + 1] == 'I') {
//			beginPos = idx;
//		}
//
//		if (paths[idx] == ' ') {
//			paths.emplace_back(command.substr(beginPos, idx - beginPos));
//			beginPos = -1;
//		}
//	}
//
//	return paths;
//}


std::vector<TranslationUnit> getTranslationUnits(const std::string& path) {
	std::vector<TranslationUnit> tu;

	auto compileCommands = getJsonConent(path);

	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(compileCommands);

	auto root = result.extract<Poco::JSON::Array::Ptr>();
	for (auto el : *root) {
		const auto& entry = el.extract<Poco::JSON::Object::Ptr>();

		const auto& file = entry->get("file");
		const auto& command = entry->get("command");
		const auto& arguments = entry->get("arguments");

		bool isValid = file.isEmpty() || !file.isString() ||
					   (!command.isEmpty() && command.isString()) ||
					   (!arguments.isEmpty() && arguments.isString());

		if (!isValid) {
			std::stringstream ss;
			entry->stringify(ss);
			std::string msg = std::string("Incorrect format of entry: \n") + ss.str();
			throw std::invalid_argument(msg);
		}

		const auto& dirStr = command.extract<std::string>();
		const auto& fileStr = file.extract<std::string>();


	}

	return tu;
}

int main(int argc, char **argv) {
	auto compilationFilePath = std::string("../compile_commands.json");

	auto translationUnits = getTranslationUnits(compilationFilePath);


	return 0;
}
