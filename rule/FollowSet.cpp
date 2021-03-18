//
// Created by laugh on 2021/3/18.
//

#include <sstream>
#include "FollowSet.h"
#include "../util/Log.h"

FollowSet::Builder::Builder(RuleItem *who) : BaseSymbolSetBuilder(who) {

}

FollowSet *FollowSet::Builder::build() {
    std::ostringstream fmt("generate first set: ");
    fmt << "FOLLOW(" << belongTo->getSymbolName() << ") = { ";
    for (auto &r : symbolSet) {
        fmt << r->getSymbolName() << ", ";
    }
    fmt << " }";
    Log::info(fmt.str());
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
