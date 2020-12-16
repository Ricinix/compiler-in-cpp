//
// Created by laugh on 2020/12/16.
//

#include "RegexPat.h"
#include <regex>

std::regex RegexPat::getRexPat() {
    std::string regexStr = "\\s*(";
    regexStr += COMMENT;
    regexStr += NUMBER;
    regexStr += STRING;
    regexStr += IDENTIFIER;
    regexStr += ")?";
    return std::regex(regexStr);
}