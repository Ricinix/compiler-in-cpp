//
// Created by laugh on 2021/3/18.
//

#ifndef DESIGN_1_BASESYMBOLSET_H
#define DESIGN_1_BASESYMBOLSET_H

#include "RuleItem.h"
#include <vector>

class BaseSymbolSet {
protected:
    std::vector<RuleItem *> symbolSet;

    RuleItem *belongTo;

    BaseSymbolSet(RuleItem *who, std::vector<RuleItem *> &symbols);

};

class BaseSymbolSetBuilder {
protected:
    std::vector<RuleItem *> symbolSet;

    RuleItem *belongTo;
public:
    explicit BaseSymbolSetBuilder(RuleItem *who);

    void addTerminalSymbol(RuleItem *ruleItem);
};

#endif //DESIGN_1_BASESYMBOLSET_H
