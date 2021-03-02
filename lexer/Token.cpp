//
// Created by laugh on 2020/12/15.
//

#include <iostream>
#include "Token.h"
#include "../domain/exception.h"

Token::Token(int line, TokenType type) {
    lineNumber = line;
    tokenType = type;
}

Token::Token(TokenType type) {
    lineNumber = -1;
    tokenType = type;
}

const TokenType &Token::getTokenType() const {
    return tokenType;
}

int Token::getNumber() const {
    throw StoneException("not number token");
}

int Token::getLineNumber() const {
    return lineNumber;
}

std::string Token::getText() const {
    return "";
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    std::string type;
    if (token.getTokenType() == TokenType::eof) {
        type = "eof";
    } else if (token.getTokenType() == TokenType::string) {
        type = "string";
    } else if (token.getTokenType() == TokenType::eol) {
        type = "eol";
    } else if (token.getTokenType() == TokenType::identifier) {
        type = "identifier";
    } else if (token.getTokenType() == TokenType::number) {
        type = "number";
    } else if (token.getTokenType() == TokenType::op) {
        type = "op";
    }

    os << ">>>>>>>>>>Token>>>>>>>>>>" << std::endl;
    os << "text: " + token.getText() << std::endl;
    os << "line: " + std::to_string(token.getLineNumber()) << std::endl;
    os << "type: " + type << std::endl;
    os << "<<<<<<<<<<Token<<<<<<<<<<";
    return os;
}

NumToken::NumToken(int line, int v) : Token(line, TokenType::number) {
    value = v;
}

std::string NumToken::getText() const {
    return std::to_string(value);
}

int NumToken::getNumber() const {
    return value;
}

IdToken::IdToken(int line, std::string &id) : Token(line, TokenType::identifier) {
    text = id;
}

std::string IdToken::getText() const {
    return text;
}

IdToken::IdToken(int line, TokenType type) : Token(line, type) {
    if (type == TokenType::eol) {
        text = "\\n";
    }
}

StrToken::StrToken(int line, std::string &str) : Token(line, TokenType::string) {
    literal = str;
}

std::string StrToken::getText() const {
    return literal;
}

OpType OpToken::getOpType(const std::string &str) {
    if (str.length() > 3) {
        return OpType::none;
    }
    if (str == "+") {
        return OpType::plus;
    }
    else if (str == "-") {
        return OpType::minus;
    }
    else if (str == "*") {
        return OpType::times;
    }
    else if (str == "/") {
        return OpType::divide;
    }
    else if (str == "%") {
        return OpType::mod;
    }
    else if (str == "==") {
        return OpType::equal;
    }
    else if (str == "<") {
        return OpType::less;
    }
    else if (str == ">") {
        return OpType::more;
    }
    else if (str == "<=") {
        return OpType::lessEqual;
    }
    else if (str == ">=") {
        return OpType::moreEqual;
    }
    else if (str == "&&") {
        return OpType::logicalAnd;
    }
    else if (str == "||") {
        return OpType::logicalOr;
    }
    else if (str == "!") {
        return OpType::logicalNot;
    }
    else if (str == "=") {
        return OpType::assign;
    }
    return OpType::none;
}

OpToken::OpToken(int line, OpType type) : Token(line, TokenType::op) {
    opType = type;
}

OpType OpToken::getOpType() const {
    return opType;
}

OpToken::OpToken(int line, OpType type, const std::string &str) : Token(line, TokenType::op) {
    rawStr = str;
    opType = type;
}

std::string OpToken::getText() const {
    return rawStr;
}
