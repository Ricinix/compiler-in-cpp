//
// Created by laugh on 2021/3/18.
//

#include <sstream>
#include "FirstSet.h"
#include "../util/Log.h"

FirstSet::FirstSet(RuleItem *who, std::vector<RuleItem *> &first, bool hasEmptySymbol) : BaseSymbolSet(who, first) {
    hasEmpty = hasEmptySymbol;
}

bool FirstSet::hasEmptySymbol() const {
    return hasEmpty;
}

FirstSet::Builder::Builder(RuleItem *who) : BaseSymbolSetBuilder(who) {

}

FirstSet *FirstSet::Builder::build() {
    std::ostringstream fmt("generate first set: ");
    fmt << "FIRST(" << belongTo->getSymbolName() << ") = { ";
    for (auto &r : symbolSet) {
        fmt << r->getSymbolName() << ", ";
    }
    fmt << " }";
    Log::info(fmt.str());
    return new FirstSet(belongTo, symbolSet, hasEmpty);
}

void FirstSet::Builder::addTerminalSymbol(RuleItem *ruleItem) {
    BaseSymbolSetBuilder::addTerminalSymbol(ruleItem);
}

RuleItem *FirstSet::Builder::getBelongSymbol() {
    return BaseSymbolSetBuilder::getBelongSymbol();
}

void FirstSet::Builder::addEmptySymbol() {
    if (hasEmpty) {
        return;
    }
    hasEmpty = true;
    addTerminalSymbol(new EmptySymbol);
}
