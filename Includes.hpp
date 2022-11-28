/*
 * Includes.hpp
 *
 *  Created on: Nov 20, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <vector>
#include <string>

class Include;

class Include {
public:
	int getLineCount();
	int getTemlateLines();
	int getCommentsLines();
	int getCodeLines();

	std::vector<Include*> getIncludes();
};

