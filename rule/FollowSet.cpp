//
// Created by laugh on 2021/3/18.
//

#include "FollowSet.h"

FollowSet::Builder::Builder(RuleItem *who) : BaseSymbolSetBuilder(who) {

}

FollowSet *FollowSet::Builder::build() {
    return new FollowSet(belongTo, symbolSet);
}

void FollowSet::Builder::addTerminalSymbol(RuleItem *ruleItem) {
    BaseSymbolSetBuilder::addTerminalSymbol(ruleItem);
}

void FollowSet::Builder::addEndSymbol() {
    addTerminalSymbol(new EndSymbol);
}

void FollowSet::Builder::concatSymbolSet(BaseSymbolSet *set) {
    for (int i = 0; i < set->SymbolNum(); ++i) {
        auto *symbol = set->getSymbolByPos(i);
        if (symbol->getRuleItemType() != RuleItemType::Empty) {
            addTerminalSymbol(symbol);
        }
    }
}

FollowSet::FollowSet(RuleItem *who, std::vector<RuleItem *> &follow) : BaseSymbolSet(who, follow) {

}
