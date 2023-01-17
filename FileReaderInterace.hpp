/*
 * FileReaderInterace.hpp
 *
 *  Created on: Dec 3, 2022
 *      Author: Adam Stepniak
 */

#pragma once

#include <string_view>

class FileReaderInterface {
public:
	virtual ~FileReaderInterface() {}

	virtual void open(const std::string& file) = 0;
	virtual void close() = 0;
	virtual std::string_view read() = 0;
};

