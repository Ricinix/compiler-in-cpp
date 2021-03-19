//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULESEQ_H
#define DESIGN_1_RULESEQ_H

#include <vector>
#include "RuleItem.h"

class RuleSeq {
private:
    std::vector<RuleItem *> ruleItemSet;
    RuleItem *startSymbol;
public:
    explicit RuleSeq(RuleItem *start);

    RuleSeq *appendNonTerminalSymbol(const std::string &name);

    RuleSeq *appendTerminalSymbol(const std::string &name);

    RuleSeq *appendTerminalSymbol(TokenType tokenType);

    RuleSeq *appendEmpty();

    RuleItem *getStartSymbol();

    RuleItem *getRuleItemByPos(int pos);

    int ruleItemNum();

    ~RuleSeq();
};


#endif //DESIGN_1_RULESEQ_H
