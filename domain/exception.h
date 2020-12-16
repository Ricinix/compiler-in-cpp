//
// Created by laugh on 2020/12/15.
//

#ifndef DESIGN_1_EXCEPTION_H
#define DESIGN_1_EXCEPTION_H

#include <string>
#include <stdexcept>
#include "../lexer/Token.h"

class StoneException: public std::runtime_error{
public:
    explicit StoneException(const std::string & msg): std::runtime_error(msg){}
};

class ParseException: public std::logic_error {
public:
    explicit ParseException(Token &t);
    explicit ParseException(std::string &msg);
    explicit ParseException(std::string &msg, Token &t);
private:
    static std::string location(Token &t);
    static std::string getErrorMsg(const char* msg, Token &t);
};

#endif //DESIGN_1_EXCEPTION_H
