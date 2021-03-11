//
// Created by laugh on 2021/3/1.
//

#include "RuleItem.h"
#include "SymbolTable.h"

RuleItem::RuleItem(const std::string &name) {
    symbolName = name;
}

std::string RuleItem::getSymbolName() {
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
}

TerminalSymbol::TerminalSymbol(TokenType type) : RuleItem("") {
    tokenType = type;
}

bool TerminalSymbol::matchToken(Token *token) {
    if (tokenType == TokenType::reserve) {
        // 如果当前的终结符没有指定TokenType，那就是在Rule中定义的关键字，按id处理，且内容得一致
        return (token->getTokenType() == TokenType::identifier || token->getTokenType() == TokenType::op)
               && token->getText() == symbolName;
    } else if (token->getTokenType() == TokenType::identifier && SymbolTable::isReservedWord(token->getText())) {
        // 假如不是终结符是关键字，而是token是关键字，则也要完全比对
        return tokenType == TokenType::reserve && token->getText() == symbolName;
    }
    return token->getTokenType() == tokenType;
}

RuleItemType TerminalSymbol::getRuleItemType() {
    return RuleItemType::Terminal;
}

EmptySymbol::EmptySymbol() : RuleItem("ε") {

}

bool EmptySymbol::matchToken(Token *token) {
    return false;
}

RuleItemType EmptySymbol::getRuleItemType() {
    return RuleItemType::Empty;
}
