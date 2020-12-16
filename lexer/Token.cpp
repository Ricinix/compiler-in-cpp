//
// Created by laugh on 2020/12/15.
//

#include "Token.h"
#include "../domain/exception.h"

Token::Token(int line, TokenType type) {
    lineNumber = line;
    tokenType = type;
}

const TokenType &Token::getTokenType() {
    return tokenType;
}

int Token::getNumber() const {
    throw StoneException("not number token");
}

int Token::getLineNumber() const {
    return lineNumber;
}

std::string Token::getText() {
    return "";
}
