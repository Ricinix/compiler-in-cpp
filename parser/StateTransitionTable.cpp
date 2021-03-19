//
// Created by laugh on 2021/3/19.
//

#include "../domain/exception.h"
#include "StateTransitionTable.h"

StateTransitionTable::StateTransitionTable(RuleSet *set) {
    ruleSet = set;
    for (int i = 0; i < ruleSet->ruleNum(); ++i) {
        auto *rule = ruleSet->getRule(i);
        for (int j = 0; j < rule->ruleSeqNum(); ++j) {
            auto *ruleSeq = rule->getRuleSeq(j);
            auto *first = ruleSet->getFirstSet(ruleSeq, 0, ruleSeq->ruleItemNum());
            for (int k = 0; k < first->SymbolNum(); ++k) {
                auto *symbol = first->getSymbolByPos(k);
                if (symbol->getRuleItemType() != RuleItemType::Empty) {
                    insert(rule->getStartSymbol(), symbol, ruleSeq);
                }
            }
            if (first->hasEmptySymbol()) {
                auto *follow = ruleSet->getFollowSet(rule->getStartSymbol());
                for (int k = 0; k < follow->SymbolNum(); ++k) {
                    insert(rule->getStartSymbol(), follow->getSymbolByPos(k), ruleSeq);
                }
            }
        }
    }
}

RuleSeq *StateTransitionTable::getRuleSeq(RuleItem *startSymbol, Token *token) {
    auto pair1 = table.find(startSymbol->getSymbolName());
    if (pair1 != table.end()) {
        for (auto &pair2 : *pair1->second) {
            if (pair2.first->matchToken(token)) {
                return pair2.second;
            }
        }
    }
    return nullptr;
}

RuleSeq *StateTransitionTable::getRuleSeq(Token *token) {
    for (int i = 0; i < ruleSet->ruleNum(); ++i) {
        auto *start = ruleSet->getRule(i)->getStartSymbol();
        auto *ruleSeq = getRuleSeq(start, token);
        if (ruleSeq != nullptr) {
            return ruleSeq;
        }
    }
    return nullptr;
}

bool StateTransitionTable::insert(RuleItem *startSymbol, RuleItem *terminal, RuleSeq *ruleSeq) {
    auto pair = table.find(startSymbol->getSymbolName());
    if (pair == table.end()) {
        auto row = new std::map<RuleItem *, RuleSeq *>();
        table[startSymbol->getSymbolName()] = row;
        (*row)[terminal] = ruleSeq;
    } else {
        auto t = *pair->second;
        for (auto &pair2 : t) {
            if (pair2.first->getSymbolName() == terminal->getSymbolName()
                && pair2.first->getRuleItemType() == terminal->getRuleItemType()) {
                throw ParseException(
                        "rule seq repeat: M[" + startSymbol->getSymbolName() + ", " + terminal->getSymbolName() + "]");
            }
        }
        t[terminal] = ruleSeq;
    }
    return true;
}
