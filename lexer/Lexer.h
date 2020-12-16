//
// Created by laugh on 2020/12/16.
//

#ifndef DESIGN_1_LEXER_H
#define DESIGN_1_LEXER_H

#include <vector>
#include <list>
#include <regex>
#include "Token.h"
#include "RegexPat.h"
#include "../util/IoUtil.h"


class Lexer {
public:
    explicit Lexer(IoUtil &ioUtil_val);

    Token *read();

    Token *peek(int i);

    ~Lexer();

private:
    std::regex pattern = RegexPat::getRexPat();
    std::list<Token *> queue;
    std::vector<Token *> ptrStore;
    bool hasMore;
    IoUtil *ioUtil_ptr;

    bool fillQueue(int i);

    Token *getEofToken();

protected:
    void readLine();

    void addToken(int lineNo, std::smatch &result);

    static std::string toStringLiteral(const std::string &s);
};


#endif //DESIGN_1_LEXER_H
