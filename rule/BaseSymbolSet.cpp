//
// Created by laugh on 2021/3/18.
//

#include "BaseSymbolSet.h"

BaseSymbolSet::BaseSymbolSet(RuleItem *who, std::vector<RuleItem *> &symbols) {
    belongTo = who;
    symbolSet = symbols;
}

void BaseSymbolSetBuilder::addTerminalSymbol(RuleItem *ruleItem) {
    symbolSet.push_back(ruleItem);
}

BaseSymbolSetBuilder::BaseSymbolSetBuilder(RuleItem *who) {
    belongTo = who;
}

RuleItem *BaseSymbolSetBuilder::getBelongSymbol() {
    return belongTo;
}
