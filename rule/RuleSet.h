//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULESET_H
#define DESIGN_1_RULESET_H

#include <map>
#include "Rule.h"
#include "FirstSet.h"
#include "FollowSet.h"

class RuleSet {
private:
    std::vector<Rule *> ruleSet;
    std::map<std::string, Rule *> ruleMap;
    std::map<std::string, FirstSet *> firstSet;
    std::map<std::string, FollowSet *> followSet;

    Rule *getRule(std::string &startSymbolName);

    FirstSet *initFirstSet(RuleItem *ruleItem);

    /**
     *
     * @param builder
     * @param ruleItem
     * @return 是否有空
     */
    bool findFirst(FirstSet::Builder &builder, RuleItem *ruleItem);

    FollowSet *initFollowSet(RuleItem *ruleItem);

public:
    Rule *makeNewRule(const std::string &name);

    ~RuleSet();

    /**
     * 根据已定文法生成语法集
     *
     * @return
     */
    static RuleSet *generate();

    int ruleNum();

    Rule *getRule(int i);

    Rule *getRule(RuleItem *startSymbol);

    FirstSet *getFirstSet(RuleItem *ruleItem);

    FollowSet *getFollowSet(RuleItem *ruleItem);
};


#endif //DESIGN_1_RULESET_H
