//
// Created by laugh on 2020/12/16.
//

#ifndef DESIGN_1_REGEXPAT_H
#define DESIGN_1_REGEXPAT_H

#include <string>
#include <sstream>
#include <regex>

namespace RegexPat {
    // 匹配注释
    const char COMMENT[] = R"((//.*))";
    // 匹配数字
    const char NUMBER[] = R"(([0-9]+))";
    // 匹配字符串
    const char STRING[] = R"("(\\"|\\\\|\\n|[^"])*")";
    // 匹配标识符（变量名、运算符、以及其他标点符号）
    const char IDENTIFIER[] = R"([A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\|\||[!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~])";
    std::regex getRexPat();
    void _concatRegex(std::ostringstream &regexStream, const std::string &part);
}


#endif //DESIGN_1_REGEXPAT_H
