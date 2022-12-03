/*
 * CMakeCommandsParserTest.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: Adam Stepniak
 */

#include <gtest/gtest.h>

#include <string>

#include "../SyntaxTreeBuilder.hpp"

using namespace core;

std::string header1 = R"(
#pragma once

#include <string>
#include <vector>

#include "Custom.hpp"
#include "nested/Custom.hpp"
#include "nexted/Custom2.hpp"
)";


// Demonstrate some basic assertions.
TEST(SyntaxTreeBuilderTest, WhenHeaderIsParsedThenResultIsAsExpected) {
//	HeaderUnit hu(header1);
//
//	EXPECT_EQ(hu.getIncludeNames());

}



