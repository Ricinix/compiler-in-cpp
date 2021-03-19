//
// Created by laugh on 2021/3/18.
//

#ifndef DESIGN_1_FOLLOWSET_H
#define DESIGN_1_FOLLOWSET_H

#include "BaseSymbolSet.h"

class FollowSet : public BaseSymbolSet {
private:
    FollowSet(RuleItem *who, std::vector<RuleItem *> &follow);
    bool hasEnd = false;
public:
    explicit FollowSet(RuleItem *who);
    bool concatSymbolSet(BaseSymbolSet *set);
    bool addTerminalSymbol(RuleItem *ruleItem);
    void addEndSymbol();
    friend std::ostream &operator<<(std::ostream &os, const FollowSet &set);
};


#endif //DESIGN_1_FOLLOWSET_H
