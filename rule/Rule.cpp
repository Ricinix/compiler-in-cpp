//
// Created by laugh on 2020/12/31.
//

#include "Rule.h"


Rule::~Rule() {
    for (auto &ruleSeq : ruleSeqSet) {
        delete ruleSeq;
        ruleSeq = nullptr;
    }
    delete startSymbol;
    startSymbol = nullptr;
}

RuleSeq *Rule::makeNewSeq() {
    auto *ruleSeq_ptr = new RuleSeq(getStartSymbol());
    ruleSeqSet.push_back(ruleSeq_ptr);
    return ruleSeq_ptr;
}

Rule::Rule(const std::string &name) {
    startName = name;
    startSymbol = new NonTerminalSymbol(name);
}

void Rule::makeEmptySeq() {
    auto *ruleSeq_ptr = new RuleSeq(getStartSymbol());
    ruleSeq_ptr->appendEmpty();
    ruleSeqSet.push_back(ruleSeq_ptr);
}

RuleItem *Rule::getStartSymbol() {
    return startSymbol;
}

int Rule::ruleSeqNum() {
    return ruleSeqSet.size();
}

RuleSeq *Rule::getRuleSeq(int i) {
    return ruleSeqSet[i];
}



