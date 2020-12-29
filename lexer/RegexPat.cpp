//
// Created by laugh on 2020/12/16.
//

#include "RegexPat.h"
#include "../util/Log.h"
#include <regex>

std::regex RegexPat::getRexPat() {
    std::ostringstream fmt;
    fmt << "\\s*(";
    fmt << COMMENT;
    _concatRegex(fmt, NUMBER);
    _concatRegex(fmt, STRING);
    _concatRegex(fmt, IDENTIFIER);
    fmt << ")?";
    Log::info("getting regex: " + fmt.str());
    return std::regex(fmt.str());
}

void RegexPat::_concatRegex(std::ostringstream &regexStream, const std::string &part) {
    regexStream << '|';
    regexStream << part;
}
