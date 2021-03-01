//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULESET_H
#define DESIGN_1_RULESET_H

#include <map>
#include <vector>
#include "Rule.h"

class RuleSet {
private:
    std::vector<Rule *> ruleSet;
    std::map<std::string, Rule *> ruleMap;

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

    Rule *getRule(std::string &startSymbolName);

    Rule *getRule(RuleItem *startSymbol);
};


#endif //DESIGN_1_RULESET_H
