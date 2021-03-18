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
