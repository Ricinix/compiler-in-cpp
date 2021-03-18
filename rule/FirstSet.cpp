//
// Created by laugh on 2021/3/18.
//

#include "FirstSet.h"

FirstSet::FirstSet(RuleItem *who, std::vector<RuleItem *> &first) : BaseSymbolSet(who, first) {

}

FirstSet::Builder::Builder(RuleItem *who) : BaseSymbolSetBuilder(who) {

}

FirstSet *FirstSet::Builder::build() {
    return new FirstSet(belongTo, symbolSet);
}
