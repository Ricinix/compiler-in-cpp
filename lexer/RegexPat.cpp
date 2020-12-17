//
// Created by laugh on 2020/12/16.
//

#include "RegexPat.h"
#include "../util/Log.h"
#include <regex>

std::regex RegexPat::getRexPat() {
    std::string regexStr = "\\s*(";
    regexStr += COMMENT;
    _concatRegex(regexStr, NUMBER);
    _concatRegex(regexStr, STRING);
    _concatRegex(regexStr, IDENTIFIER);
    regexStr += ")?";
    Log::info("getting regex: " + regexStr);
    return std::regex(regexStr);
}

void RegexPat::_concatRegex(std::string &regexStr, const std::string &part) {
    regexStr += '|';
    regexStr += part;
}
