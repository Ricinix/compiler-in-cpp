//
// Created by laugh on 2021/3/18.
//

#ifndef DESIGN_1_FOLLOWSET_H
#define DESIGN_1_FOLLOWSET_H

#include "BaseSymbolSet.h"

class FollowSet : public BaseSymbolSet {
private:
    FollowSet(RuleItem *who, std::vector<RuleItem *> &follow);
public:
    class Builder : BaseSymbolSetBuilder {
    public:
        Builder(RuleItem *who);
        FollowSet *build();
    };
};


#endif //DESIGN_1_FOLLOWSET_H
