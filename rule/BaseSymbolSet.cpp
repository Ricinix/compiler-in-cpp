//
// Created by laugh on 2021/3/18.
//

#include "BaseSymbolSet.h"

BaseSymbolSet::BaseSymbolSet(RuleItem *who, std::vector<RuleItem *> &symbols) {
    belongTo = who;
    symbolSet = symbols;
}

int BaseSymbolSet::SymbolNum() {
    return symbolSet.size();
}

RuleItem *BaseSymbolSet::getSymbolByPos(int i) {
    return symbolSet[i];
}

bool BaseSymbolSet::cross(BaseSymbolSet *set) {
    for (int i = 0; i < set->SymbolNum(); ++i) {
        for (auto &symbol : symbolSet) {
            auto *other = set->getSymbolByPos(i);
            if (symbol == other || (symbol->getRuleItemType() == other->getRuleItemType()
                                   && symbol->getSymbolName() == other->getSymbolName())) {
                return true;
            }
        }
    }
    return false;
}

void BaseSymbolSetBuilder::addTerminalSymbol(RuleItem *ruleItem) {
    for (auto &item : symbolSet) {
        if (item == ruleItem || (item->getSymbolName() == ruleItem->getSymbolName()
                                 && item->getRuleItemType() == ruleItem->getRuleItemType())) {
            return;
        }
    }
    symbolSet.push_back(ruleItem);
}

BaseSymbolSetBuilder::BaseSymbolSetBuilder(RuleItem *who) {
    belongTo = who;
}

RuleItem *BaseSymbolSetBuilder::getBelongSymbol() {
    return belongTo;
}

void BaseSymbolSetBuilder::concatSymbolSet(BaseSymbolSet *set) {
    for (int i = 0; i < set->SymbolNum(); ++i) {
        addTerminalSymbol(set->getSymbolByPos(i));
    }
}
