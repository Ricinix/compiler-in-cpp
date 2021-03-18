//
// Created by laugh on 2021/3/18.
//

#ifndef DESIGN_1_FIRSTSET_H
#define DESIGN_1_FIRSTSET_H

#include "BaseSymbolSet.h"

class FirstSet : public BaseSymbolSet {
private:
    bool hasEmpty;
    int multipleNum;

    FirstSet(RuleItem *who, std::vector<RuleItem *> &first, bool hasEmptySymbol, int isMultiple);

public:
    bool hasEmptySymbol() const;

    class Builder : BaseSymbolSetBuilder {
    private:
        bool hasEmpty = false;
        int multipleNum = 1;
    public:
        explicit Builder(RuleItem *who);

        void setMultipleNum(int multiple);

        void addTerminalSymbol(RuleItem *ruleItem) override;

        void concatSymbolSet(BaseSymbolSet *set) override;

        void addEmptySymbol();

        RuleItem *getBelongSymbol() override;

        FirstSet *build();
    };
};


#endif //DESIGN_1_FIRSTSET_H
