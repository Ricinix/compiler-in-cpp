//
// Created by laugh on 2021/3/1.
//

#include "RuleSet.h"

Rule *RuleSet::makeNewRule(const std::string &name) {
    Rule *rule_ptr = new Rule(name);
    ruleSet.push_back(rule_ptr);
    ruleMap[name] = rule_ptr;
    return rule_ptr;
}

RuleSet::~RuleSet() {
    for (auto &rule_ptr : ruleSet) {
        delete rule_ptr;
        rule_ptr = nullptr;
    }
    ruleSet.clear();
    ruleMap.clear();
}

RuleSet *RuleSet::generate() {
    auto *ruleSet = new RuleSet();

    // program 语法，包含了3个新产生式
    auto *program = ruleSet->makeNewRule("program");
    program->makeNewSeq()->appendNonTerminalSymbol("statementOrNone")->appendNonTerminalSymbol("lineEnd")
    ->appendNonTerminalSymbol("program4");
    auto *program2 = ruleSet->makeNewRule("statementOrNone");
    program2->makeNewSeq()->appendNonTerminalSymbol("statement");
    program2->makeEmptySeq();
    auto *lineEnd = ruleSet->makeNewRule("lineEnd");
    lineEnd->makeNewSeq()->appendTerminalSymbol(";");
    lineEnd->makeNewSeq()->appendTerminalSymbol(TokenType::eol);
    // 增加program对多条statement的识别
    auto *program4 = ruleSet->makeNewRule("program4");
    program4->makeNewSeq()->appendNonTerminalSymbol("program");
    program4->makeEmptySeq();

    // statement 语法，包含了2个新产生式
    auto *statement = ruleSet->makeNewRule("statement");
    statement->makeNewSeq()->appendTerminalSymbol(RW_IF)->appendNonTerminalSymbol("expr")
            ->appendNonTerminalSymbol("block")->appendNonTerminalSymbol("statement2");

    statement->makeNewSeq()->appendTerminalSymbol(RW_WHILE)->appendNonTerminalSymbol("expr")
            ->appendNonTerminalSymbol("block");
    statement->makeNewSeq()->appendNonTerminalSymbol("simple");
    auto *statement2 = ruleSet->makeNewRule("statement2");
    statement2->makeNewSeq()->appendTerminalSymbol(RW_ELSE)->appendNonTerminalSymbol("block");
    statement2->makeEmptySeq();

    // simple 语法，包含了1个新产生式
    auto *simple = ruleSet->makeNewRule("simple");
    simple->makeNewSeq()->appendNonTerminalSymbol("expr");

    // block 语法，包含了2个新产生式
    auto *block = ruleSet->makeNewRule("block");
    block->makeNewSeq()->appendTerminalSymbol("{")->appendNonTerminalSymbol("statementOrNone")
            ->appendNonTerminalSymbol("block2")->appendTerminalSymbol("}");
    auto *block2 = ruleSet->makeNewRule("block2");
    block2->makeNewSeq()->appendNonTerminalSymbol("lineEnd")->appendNonTerminalSymbol("statementOrNone")
            ->appendNonTerminalSymbol("block2");
    block2->makeEmptySeq();

    // expr 语法，包含了2个新产生式
    auto *expr = ruleSet->makeNewRule("expr");
    expr->makeNewSeq()->appendNonTerminalSymbol("factor")->appendNonTerminalSymbol("expr2");
    auto *expr2 = ruleSet->makeNewRule("expr2");
    expr2->makeNewSeq()->appendTerminalSymbol(TokenType::op)->appendNonTerminalSymbol("factor")
            ->appendNonTerminalSymbol("expr2");
    expr2->makeEmptySeq();

    // factor 语法，包含了1个新产生式
    auto *factor = ruleSet->makeNewRule("factor");
    factor->makeNewSeq()->appendTerminalSymbol("-")->appendNonTerminalSymbol("primary");
    factor->makeNewSeq()->appendNonTerminalSymbol("primary");

    // primary 语法，包含了1个新产生式
    auto *primary = ruleSet->makeNewRule("primary");
    primary->makeNewSeq()->appendTerminalSymbol("(")->appendNonTerminalSymbol("expr")
            ->appendTerminalSymbol(")");
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::number);
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::identifier);
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::string);

    return ruleSet;
}

int RuleSet::ruleNum() {
    return ruleSet.size();
}

Rule *RuleSet::getRule(int i) {
    return ruleSet[i];
}

Rule *RuleSet::getRule(std::string &startSymbolName) {
    auto rulePair = ruleMap.find(startSymbolName);
    if (rulePair != ruleMap.end()) {
        return rulePair->second;
    }
    return nullptr;
}

Rule *RuleSet::getRule(RuleItem *startSymbol) {
    std::string symbolName = startSymbol->getSymbolName();
    return getRule(symbolName);
}
