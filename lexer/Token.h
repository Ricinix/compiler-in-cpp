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

    virtual const std::string &getText() const;

    const TokenType &getTokenType() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    TokenType tokenType;
    int lineNumber;
};

class NumToken : public Token {
private:
    int value;
    std::string rawStr;
public:
    NumToken(int line, int v);

    const std::string &getText() const override;

    int getNumber() const override;


};

class IdToken : public Token {
public:
    IdToken(int line, std::string &id);

    IdToken(int line, TokenType type);

    const std::string &getText() const override;

private:
    std::string text;
    static TokenType checkType(const std::string &m);
};

class StrToken : public Token {
public:
    StrToken(int line, std::string &str);

    const std::string &getText() const override;

private:
    std::string literal;
};

class OpToken : public Token {
private:
    OpType opType;
    std::string rawStr;
public:
    static OpType getOpType(const std::string &str);

    OpToken(int line, OpType type);

    OpToken(int line, OpType type, const std::string &str);

    OpType getOpType() const;

    const std::string &getText() const override;
};

#endif //DESIGN_1_TOKEN_H
