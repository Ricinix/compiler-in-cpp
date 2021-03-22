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
    explicit ParseException(const Token &t);
    explicit ParseException(const std::string &msg);
    explicit ParseException(const std::string &msg, const Token &t);
private:
    static std::string location(const Token &t);
    static std::string getErrorMsg(const char* msg, const Token &t);
};

class DesignException : public std::logic_error {
public:
    explicit DesignException(const std::string &msg);
};

class IoException: public std::invalid_argument {
public:
    explicit IoException(const std::string &msg);
};

class IndexOutOfBoundsException: public std::invalid_argument {
public:
    explicit IndexOutOfBoundsException(const std::string &msg);
    explicit IndexOutOfBoundsException(int i);
private:
    static std::string generateMsg(int i);
};

#endif //DESIGN_1_EXCEPTION_H
