//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_RULESET_H
#define DESIGN_1_RULESET_H

#include <memory>
#include <vector>
#include "Rule.h"

class RuleSet {
private:
    std::vector<Rule *> ruleSet;

public:
    Rule *makeNewRule(const std::string &name);

    ~RuleSet();

    /**
     * 根据已定文法生成语法集
     *
     * @return
     */
    static std::unique_ptr<RuleSet> generate();
};


#endif //DESIGN_1_RULESET_H
