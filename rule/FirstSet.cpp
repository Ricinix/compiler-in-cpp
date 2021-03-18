//
// Created by laugh on 2021/3/18.
//

#include <sstream>
#include "FirstSet.h"
#include "../util/Log.h"

FirstSet::FirstSet(RuleItem *who, std::vector<RuleItem *> &first) : BaseSymbolSet(who, first) {

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
    return new FirstSet(belongTo, symbolSet);
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
