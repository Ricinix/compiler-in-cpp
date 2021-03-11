//
// Created by laugh on 2020/12/16.
//

#include <sstream>
#include "exception.h"
#include "../util/Log.h"

ParseException::ParseException(const Token &t) : std::logic_error(getErrorMsg("", t)) {
    Log::error(getErrorMsg("", t));
}

std::string ParseException::getErrorMsg(const char *msg, const Token &t) {
    return "syntax error around" + location(t) + ". " + msg;
}

ParseException::ParseException(const std::string &msg, const Token &t) : std::logic_error(getErrorMsg(msg.c_str(), t)) {
    Log::error(getErrorMsg(msg.c_str(), t));
}

ParseException::ParseException(const std::string &msg) : std::logic_error(msg.c_str()) {
    Log::error(msg);
}

std::string ParseException::location(const Token &t) {
    if (t.getTokenType() == TokenType::eof) {
        return "the last line";
    }
    return "\"" + t.getText() + "\" at line " + std::to_string(t.getLineNumber());
}

IoException::IoException(const std::string &msg): std::invalid_argument(msg) {
    Log::error(msg);
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const std::string &msg) : invalid_argument(msg) {
    Log::error(msg);
}

IndexOutOfBoundsException::IndexOutOfBoundsException(int i): std::invalid_argument(generateMsg(i)) {
    Log::error(generateMsg(i));
}

std::string IndexOutOfBoundsException::generateMsg(int i) {
    using namespace std;
    ostringstream fmt;
    fmt << "index " << i << "is out of bounds";
    return fmt.str();
}
