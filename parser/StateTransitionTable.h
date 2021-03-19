//
// Created by laugh on 2021/3/19.
//

#ifndef DESIGN_1_STATETRANSITIONTABLE_H
#define DESIGN_1_STATETRANSITIONTABLE_H

#include "../rule/RuleSet.h"

class StateTransitionTable {
private:
    std::map<std::string, std::map<RuleItem *, RuleSeq *> *> table;
    RuleSet *ruleSet;

    RuleSeq *getRuleSeq(RuleItem *startSymbol, Token *token);

    bool insert(RuleItem *startSymbol, RuleItem *terminal, RuleSeq * ruleSeq);

public:
    explicit StateTransitionTable(RuleSet *set);

    RuleSeq *getRuleSeq(Token *token);
};


#endif //DESIGN_1_STATETRANSITIONTABLE_H
