//
// Created by laugh on 2020/12/15.
//

#ifndef DESIGN_1_TOKEN_H
#define DESIGN_1_TOKEN_H

#include <string>
#include "../domain/constant.h"

class Token {
public:
    explicit Token(int line, TokenType type);

    explicit Token(TokenType type);

    int getLineNumber() const;

    virtual int getNumber() const;

    virtual std::string getText() const;

    const TokenType &getTokenType() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    TokenType tokenType;
    int lineNumber;
};

class NumToken : public Token {
public:
    NumToken(int line, int v);

    std::string getText() const override;

    int getNumber() const override;

private:
    int value;

};

class IdToken : public Token {
public:
    IdToken(int line, std::string &id);

    IdToken(int line, TokenType type);

    std::string getText() const override;

private:
    std::string text;
};

class StrToken : public Token {
public:
    StrToken(int line, std::string &str);

    std::string getText() const override;

private:
    std::string literal;
};

class OpToken : public Token {
private:
    OpType opType;
public:
    static OpType getOpType(const std::string &str);

    OpToken(int line, OpType type);

    OpType getOpType() const;
};

#endif //DESIGN_1_TOKEN_H
