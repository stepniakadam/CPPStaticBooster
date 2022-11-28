/*
 * CMakeCommandsParser.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "CMakeCommandsParser.hpp"

std::string getFileConent(const std::string& path) {
	std::ifstream compileCommands(path);
	std::string json((std::istreambuf_iterator<char>(compileCommands)),
	                  std::istreambuf_iterator<char>());

	return json;
}

int main(int argc, char **argv) {
	auto compilationFilePath = std::string("../compile_commands.json");
	auto content = getFileConent(compilationFilePath);

	parser::CMakeCommandsParser cp;
	auto translationUnits = cp.getTranslationUnits(content);

	return 0;
}
