//
// Created by laugh on 2020/12/31.
//

#include "Rule.h"


Rule::~Rule() {
    for (auto &ruleSeq : ruleSeqSet) {
        delete ruleSeq;
        ruleSeq = nullptr;
    }
}

RuleSeq *Rule::makeNewSeq() {
    auto ruleSeq_ptr = new RuleSeq();
    ruleSeqSet.push_back(ruleSeq_ptr);
    return ruleSeq_ptr;
}

Rule::Rule(const std::string &name) {
    startName = name;
}

void Rule::makeEmptySeq() {
    auto ruleSeq_ptr = new RuleSeq();
    ruleSeq_ptr->appendEmpty();
    ruleSeqSet.push_back(ruleSeq_ptr);
}

