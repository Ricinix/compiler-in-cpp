//
// Created by laugh on 2020/12/16.
//

#include "RegexPat.h"
#include "../util/Log.h"
#include <regex>

std::regex RegexPat::getRexPat() {
    std::string regexStr = "\\s*(";
    regexStr += COMMENT;
    regexStr += '|';
    regexStr += NUMBER;
    regexStr += '|';
    regexStr += STRING;
    regexStr += '|';
    regexStr += IDENTIFIER;
    regexStr += ")?";
    Log::info("getting regex: " + regexStr);
    return std::regex(regexStr);
}