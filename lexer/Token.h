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

    int getLineNumber() const;

    int getNumber() const;

    std::string getText();

    const TokenType& getTokenType();
private:
    TokenType tokenType;
    int lineNumber;
};


#endif //DESIGN_1_TOKEN_H
