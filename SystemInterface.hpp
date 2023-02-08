/*
 * SystemInterface.hpp
 *
 *  Created on: Dec 6, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <string>

class SystemInterface {
public:
	virtual ~SystemInterface() {}
	virtual bool directoryExists(const std::string& dir) = 0;
};
