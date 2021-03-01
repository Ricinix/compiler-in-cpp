//
// Created by laugh on 2021/3/1.
//

#include "RuleItem.h"

RuleItem::RuleItem(const std::string &name) {
    symbolName = name;
}

NonTerminalSymbol::NonTerminalSymbol(const std::string &name) : RuleItem(name) {

}

TerminalSymbol::TerminalSymbol(const std::string &name) : RuleItem(name) {
    tokenType = TokenType::none;
}

TerminalSymbol::TerminalSymbol(TokenType type) : RuleItem("") {
    tokenType = type;
}

EmptySymbol::EmptySymbol() : RuleItem("") {

}
