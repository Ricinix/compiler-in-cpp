//
// Created by laugh on 2020/12/15.
//

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
