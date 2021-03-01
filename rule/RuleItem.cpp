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

bool RuleItem::isTerminal() {
    return true;
}

bool RuleItem::matchToken(Token *token) {
    return false;
}

NonTerminalSymbol::NonTerminalSymbol(const std::string &name) : RuleItem(name) {

}

bool NonTerminalSymbol::isTerminal() {
    return false;
}

bool NonTerminalSymbol::matchToken(Token *token) {
    return false;
}

TerminalSymbol::TerminalSymbol(const std::string &name) : RuleItem(name) {
    tokenType = TokenType::none;
}

TerminalSymbol::TerminalSymbol(TokenType type) : RuleItem("") {
    tokenType = type;
}

bool TerminalSymbol::isTerminal() {
    return true;
}

bool TerminalSymbol::matchToken(Token *token) {
    if (tokenType == TokenType::none) {
        return token->getTokenType() == TokenType::identifier && token->getText() == symbolName;
    }
    return token->getTokenType() == tokenType;
}

EmptySymbol::EmptySymbol() : RuleItem("") {

}

bool EmptySymbol::isTerminal() {
    return true;
}

bool EmptySymbol::matchToken(Token *token) {
    return false;
}
