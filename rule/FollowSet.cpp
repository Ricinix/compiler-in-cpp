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

FollowSet::FollowSet(RuleItem *who, std::vector<RuleItem *> &follow) : BaseSymbolSet(who, follow) {

}
