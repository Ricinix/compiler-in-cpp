//
// Created by laugh on 2021/3/1.
//

#include "RuleItem.h"

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
    tokenType = TokenType::none;
}

TerminalSymbol::TerminalSymbol(TokenType type) : RuleItem("") {
    tokenType = type;
}

bool TerminalSymbol::matchToken(Token *token) {
    if (tokenType == TokenType::none) {
        return token->getTokenType() == TokenType::identifier && token->getText() == symbolName;
    }
    return token->getTokenType() == tokenType;
}

RuleItemType TerminalSymbol::getRuleItemType() {
    return RuleItemType::Terminal;
}

EmptySymbol::EmptySymbol() : RuleItem("") {

}

bool EmptySymbol::matchToken(Token *token) {
    return false;
}

RuleItemType EmptySymbol::getRuleItemType() {
    return RuleItemType::Empty;
}
