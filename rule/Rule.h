//
// Created by laugh on 2020/12/31.
//

#ifndef DESIGN_1_RULE_H
#define DESIGN_1_RULE_H

#include "RuleSeq.h"
#include <string>

class Rule {
private:
    /**
     * 每个RuleSeq之间呈或关系
     */
    std::vector<RuleSeq*> ruleSeqSet;
    std::string startName;
    RuleItem* startSymbol;
public:
    explicit Rule(const std::string &name);
    ~Rule();
    RuleSeq* makeNewSeq();
    void makeEmptySeq();
    RuleItem* getStartSymbol();
    int ruleSeqNum();
    RuleSeq* getRuleSeq(int i);
};


#endif //DESIGN_1_RULE_H
