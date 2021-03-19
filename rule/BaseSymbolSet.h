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

    explicit BaseSymbolSet(RuleItem *who);

public:
    int SymbolNum();

    RuleItem *getSymbolByPos(int i);

    /**
     * 是否相交
     * @param set
     * @return
     */
    bool cross(BaseSymbolSet *set);
};

class BaseSymbolSetBuilder {
protected:
    std::vector<RuleItem *> symbolSet;

    RuleItem *belongTo;

    explicit BaseSymbolSetBuilder(RuleItem *who);

public:
    virtual RuleItem *getBelongSymbol();

    virtual void concatSymbolSet(BaseSymbolSet *set);

    virtual void addTerminalSymbol(RuleItem *ruleItem);
};

#endif //DESIGN_1_BASESYMBOLSET_H
