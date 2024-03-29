//
// Created by laugh on 2021/3/1.
//

#include "RuleItem.h"
#include "SymbolTable.h"

RuleItem::RuleItem(const std::string &name) {
    symbolName = name;
}

const std::string &RuleItem::getSymbolName() {
    return symbolName;
}

bool RuleItem::matchToken(Token *token) {
    return false;
}

RuleItemType RuleItem::getRuleItemType() {
    return RuleItemType::Empty;
}

NonTerminalSymbol::NonTerminalSymbol(const std::string &name) : RuleItem(name) {

}

bool NonTerminalSymbol::matchToken(Token *token) {
    return false;
}

RuleItemType NonTerminalSymbol::getRuleItemType() {
    return RuleItemType::NonTerminal;
}

TerminalSymbol::TerminalSymbol(const std::string &name) : RuleItem(name) {
    tokenType = TokenType::reserve;
    terminalName = name;
}

TerminalSymbol::TerminalSymbol(TokenType type) : RuleItem("") {
    tokenType = type;
    if (tokenType == TokenType::string) {
        terminalName = "STRING";
    } else if (tokenType == TokenType::op) {
        terminalName = "OP";
    } else if (tokenType == TokenType::number) {
        terminalName = "NUMBER";
    } else if (tokenType == TokenType::identifier) {
        terminalName = "IDENTIFIER";
    } else if (tokenType == TokenType::eof) {
        terminalName = "EOF";
    } else if (tokenType == TokenType::eol) {
        terminalName = "EOL";
    } else if (tokenType == TokenType::none) {
        terminalName = "NONE";
    }
}

bool TerminalSymbol::matchToken(Token *token) {
    if (tokenType == TokenType::reserve) {
        // 如果当前的终结符没有指定TokenType，那就是在Rule中定义的关键字，按id处理，且内容得一致
        return (token->getTokenType() == TokenType::reserve || token->getTokenType() == TokenType::op)
               && token->getText() == symbolName;
    } else if (token->getTokenType() == TokenType::reserve) {
        // 假如不是终结符是关键字，而是token是关键字，则也要完全比对
        return tokenType == TokenType::reserve && token->getText() == symbolName;
    }
    return token->getTokenType() == tokenType;
}

RuleItemType TerminalSymbol::getRuleItemType() {
    return RuleItemType::Terminal;
}

const std::string &TerminalSymbol::getSymbolName() {
    return terminalName;
}

EmptySymbol::EmptySymbol() : RuleItem("ε") {

}

bool EmptySymbol::matchToken(Token *token) {
    return false;
}

RuleItemType EmptySymbol::getRuleItemType() {
    return RuleItemType::Empty;
}

bool EndSymbol::matchToken(Token *token) {
    if (token->getTokenType() == TokenType::eof) {
        return true;
    }
    return false;
}

RuleItemType EndSymbol::getRuleItemType() {
    return RuleItemType::End;
}

EndSymbol::EndSymbol() : RuleItem("$") {

}
