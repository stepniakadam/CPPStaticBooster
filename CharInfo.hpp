/*
 * CharInfo.hpp
 *
 *  Created on: Jan 15, 2023
 *      Author: Adam Stepniak
 */
#pragma once

#include <cstdint>

namespace character {
// Definitions below are part of Clang project:
// Changed:
// - ajdusted namespaces
// - removed:  LLVM_READONLY
//===--- clang/Basic/CharInfo.h - Classifying ASCII Characters --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
enum {
CHAR_HORZ_WS  = 0x0001,  // '\t', '\f', '\v'.  Note, no '\0'
CHAR_VERT_WS  = 0x0002,  // '\r', '\n'
CHAR_SPACE    = 0x0004,  // ' '
CHAR_DIGIT    = 0x0008,  // 0-9
CHAR_XLETTER  = 0x0010,  // a-f,A-F
CHAR_UPPER    = 0x0020,  // A-Z
CHAR_LOWER    = 0x0040,  // a-z
CHAR_UNDER    = 0x0080,  // _
CHAR_PERIOD   = 0x0100,  // .
CHAR_RAWDEL   = 0x0200,  // {}[]#<>%:;?*+-/^&|~!=,"'
CHAR_PUNCT    = 0x0400   // `$@()
};

enum {
CHAR_XUPPER = CHAR_XLETTER | CHAR_UPPER,
CHAR_XLOWER = CHAR_XLETTER | CHAR_LOWER
};

extern const uint16_t InfoTable[256];

/// Returns true if this character is horizontal ASCII whitespace:
/// ' ', '\\t', '\\f', '\\v'.
///
/// Note that this returns false for '\\0'.
inline bool isHorizontalWhitespace(unsigned char c) {
  return (InfoTable[c] & (CHAR_HORZ_WS|CHAR_SPACE)) != 0;
}

/// Returns true if this character is vertical ASCII whitespace: '\\n', '\\r'.
///
/// Note that this returns false for '\\0'.
inline bool isVerticalWhitespace(unsigned char c) {
  return (InfoTable[c] & CHAR_VERT_WS) != 0;
}

/// Return true if this character is an ASCII letter: [a-zA-Z]
inline bool isLetter(unsigned char c) {
  return (InfoTable[c] & (CHAR_UPPER|CHAR_LOWER)) != 0;
}

/// Return true if this character is an ASCII letter or digit: [a-zA-Z0-9]
inline bool isAlphanumeric(unsigned char c) {
  return (InfoTable[c] & (CHAR_DIGIT|CHAR_UPPER|CHAR_LOWER)) != 0;
}

/// Returns true if this is a valid first character of a C identifier,
/// which is [a-zA-Z_].
inline bool isAsciiIdentifierStart(unsigned char c, bool AllowDollar = false) {
  if (InfoTable[c] & (CHAR_UPPER|CHAR_LOWER|CHAR_UNDER))
    return true;
  return AllowDollar && c == '$';
}

/// Returns true if this is a body character of a C identifier,
/// which is [a-zA-Z0-9_].
inline bool isAsciiIdentifierContinue(unsigned char c, bool AllowDollar = false) {
  if (InfoTable[c] & (CHAR_UPPER|CHAR_LOWER|CHAR_DIGIT|CHAR_UNDER))
    return true;
  return AllowDollar && c == '$';
}
}  // namespace character
// End of Clang definitions
