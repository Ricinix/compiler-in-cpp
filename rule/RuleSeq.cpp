//
// Created by laugh on 2021/3/1.
//

#include "RuleSeq.h"
#include "SymbolTable.h"

RuleSeq::~RuleSeq() {
    for (auto &item : ruleItemSet) {
        delete item;
        item = nullptr;
    }
}

RuleSeq* RuleSeq::appendNonTerminalSymbol(const std::string &name) {
    auto* item = new NonTerminalSymbol(name);
    ruleItemSet.push_back(item);
    return this;
}

RuleSeq* RuleSeq::appendTerminalSymbol(const std::string &name) {
    auto* item = new TerminalSymbol(name);
    ruleItemSet.push_back(item);
    SymbolTable::addReservedWord(name);
    return this;
}

RuleSeq* RuleSeq::appendTerminalSymbol(TokenType tokenType) {
    auto* item = new TerminalSymbol(tokenType);
    ruleItemSet.push_back(item);
    return this;
}

RuleSeq* RuleSeq::appendEmpty() {
    auto* item = new EmptySymbol();
    ruleItemSet.push_back(item);
    return this;
}

RuleItem *RuleSeq::getRuleItemByPos(int pos) {
    return ruleItemSet[pos];
}

int RuleSeq::ruleItemNum() {
    return ruleItemSet.size();
}

