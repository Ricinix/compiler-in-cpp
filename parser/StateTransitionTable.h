//
// Created by laugh on 2021/3/19.
//

#ifndef DESIGN_1_STATETRANSITIONTABLE_H
#define DESIGN_1_STATETRANSITIONTABLE_H

#include "../rule/RuleSet.h"

class StateTransitionTable {
private:
    class TableRow {
    private:
        std::vector<std::pair<RuleItem *, RuleSeq *>> list;
        std::map<std::string, std::pair<RuleItem *, RuleSeq *>> map;

        static const std::string &getKey(RuleItem *terminal);
        static std::string getKey(Token *token);
    public:
        bool append(RuleItem *terminal, RuleSeq *ruleSeq);

        RuleSeq *get(RuleItem *terminal);

        RuleSeq *get(Token *token);
    };

    std::map<std::string, TableRow *> table;
    RuleSet *ruleSet;

    bool insert(RuleItem *startSymbol, RuleItem *terminal, RuleSeq *ruleSeq);

public:
    explicit StateTransitionTable(RuleSet *set);

    RuleSeq *getRuleSeq(RuleItem *startSymbol, Token *token);

    RuleSeq *getRuleSeq(Token *token);
};


#endif //DESIGN_1_STATETRANSITIONTABLE_H
