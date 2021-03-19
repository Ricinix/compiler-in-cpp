//
// Created by laugh on 2021/3/18.
//

#include <sstream>
#include "FollowSet.h"
#include "../util/Log.h"

FollowSet::FollowSet(RuleItem *who, std::vector<RuleItem *> &follow) : BaseSymbolSet(who, follow) {

}

FollowSet::FollowSet(RuleItem *who) : BaseSymbolSet(who) {

}

bool FollowSet::concatSymbolSet(BaseSymbolSet *set) {
    bool hasNew = false;
    for (int i = 0; i < set->SymbolNum(); ++i) {
        auto *symbol = set->getSymbolByPos(i);
        if (symbol->getRuleItemType() != RuleItemType::Empty) {
            if (addTerminalSymbol(symbol)) {
                hasNew = true;
            }
        }
    }
    return hasNew;
}

bool FollowSet::addTerminalSymbol(RuleItem *ruleItem) {
    for (auto &item : symbolSet) {
        if (item == ruleItem || (item->getSymbolName() == ruleItem->getSymbolName()
                                 && item->getRuleItemType() == ruleItem->getRuleItemType())) {
            return false;
        }
    }
    symbolSet.push_back(ruleItem);
    return true;
}

void FollowSet::addEndSymbol() {
    if (hasEnd) {
        return;
    }
    hasEnd = true;
    addTerminalSymbol(new EndSymbol);
}

std::ostream &operator<<(std::ostream &os, const FollowSet &set) {
    os << "generate first set: ";
    os << "FOLLOW(" << set.belongTo->getSymbolName() << ") = { ";
    for (auto &r : set.symbolSet) {
        os << r->getSymbolName() << ", ";
    }
    os << " }";
    return os;
}
