//
// Created by laugh on 2020/12/16.
//

#ifndef DESIGN_1_REGEXPAT_H
#define DESIGN_1_REGEXPAT_H

#include <string>
#include <regex>

namespace RegexPat {
    const char COMMENT[] = "(//.*)";
    const char NUMBER[] = "([0-9]+)";
    const char STRING[] = R"("(\\"|\\\\|\\n|[^"])*")";
    const char IDENTIFIER[] = R"([A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\|\|\||\p{Punct})";
    std::regex getRexPat();
}


#endif //DESIGN_1_REGEXPAT_H
