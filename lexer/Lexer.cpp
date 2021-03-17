//
// Created by laugh on 2020/12/16.
//
#include <regex>
#include <sstream>
#include "Lexer.h"
#include "../domain/exception.h"

Lexer::Lexer(IoUtil &ioUtil_val) {
    ioUtil_ptr = &ioUtil_val;
    hasMore = true;
}

Token *Lexer::read() {
    if (fillQueue(0)) {
        Token *t = queue.front();
        queue.pop_front();
        return t;
    }
    return getEofToken();
}

Token *Lexer::peek(int i) {
    if (fillQueue(i)) {
        int j = 0;
        for (auto &ptr: queue) {
            if (j++ == i) {
                return ptr;
            }
        }
        return nullptr;
    } else {
        return getEofToken();
    }
}

Lexer::~Lexer() = default;

Token *Lexer::getEofToken() {
    auto *eofToken = new Token(TokenType::eof);
    ptrStore.push_back(eofToken);
    return eofToken;
}

bool Lexer::fillQueue(int i) {
    while (i >= queue.size()) {
        if (hasMore) {
            readLine();
        } else {
            return false;
        }
    }
    return true;
}

void Lexer::readLine() {
    std::string line = ioUtil_ptr->readLine();
    Log::info("read: " + line);
    if (line.empty()) {
        hasMore = false;
        return;
    }
    int lineNo = ioUtil_ptr->getLineNumber();
    std::smatch result;
    int pos = 0;
    int endPos = line.length();
    while (pos < endPos) {
        if (std::regex_search(line.cbegin() + pos, line.cend(), result, pattern)) {
            addToken(lineNo, result);
            pos += result.length() + result.position();
        } else {
            const std::string msg = "bad token at line " + std::to_string(lineNo);
            throw ParseException(msg);
        }
    }
    queue.push_back(new IdToken(lineNo, TokenType::eol));
}

void Lexer::addToken(int lineNo, std::smatch &result) {
    std::string m = result[1].str();
    if (!m.empty()) {
        if (result[2].str().empty()) {
            Token *t_ptr;
            if (!result[3].str().empty()) {
                t_ptr = new NumToken(lineNo, std::stoi(m));

            } else if (!result[4].str().empty()) {
                std::string literal = toStringLiteral(m);
                t_ptr = new StrToken(lineNo, literal);
            } else {
                OpType opType = OpToken::getOpType(m);
                if (opType != OpType::none) {
                    t_ptr = new OpToken(lineNo, opType, m);
                } else {
                    t_ptr = new IdToken(lineNo, m);
                }
            }
            queue.push_back(t_ptr);
        }
    }
}

std::string Lexer::toStringLiteral(const std::string &s) {
    std::ostringstream fmt;
    unsigned int len = s.length() - 1;
    for (unsigned int i = 1; i < len; ++i) {
        char c = s[i];
        if (c == '\\' && i + 1 < len) {
            char c2 = s[i + 1];
            if (c2 == '"' || c2 == '\\') {
                // 把"和\前面的转移字符去掉
                c = s[++i];
            } else if (c2 == 'n') {
                // 将\n两个字符合成一个转义字符
                ++i;
                c = '\n';
            }
        }
        fmt << c;
    }
    return fmt.str();
}
