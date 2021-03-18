//
// Created by laugh on 2021/3/18.
//

#ifndef DESIGN_1_FIRSTSET_H
#define DESIGN_1_FIRSTSET_H

#include "BaseSymbolSet.h"

class FirstSet : public BaseSymbolSet {
private:
    FirstSet(RuleItem *who, std::vector<RuleItem *> &first);

public:
    class Builder : BaseSymbolSetBuilder {
    private:
        bool hasEmpty = false;
    public:
        explicit Builder(RuleItem *who);

        void addTerminalSymbol(RuleItem *ruleItem) override;

        void addEmptySymbol();

        RuleItem * getBelongSymbol() override;

        FirstSet *build();
    };
};


#endif //DESIGN_1_FIRSTSET_H
