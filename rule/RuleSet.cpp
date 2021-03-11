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

    // program 语法，包含了4个新产生式
    auto *program = ruleSet->makeNewRule(NS_PROGRAM);
    program->makeNewSeq()->appendNonTerminalSymbol(NS_PROGRAM_BODY)->appendNonTerminalSymbol(NS_LINE_END)
            ->appendNonTerminalSymbol(NS_PROGRAM_STAR);
    auto *program2 = ruleSet->makeNewRule(NS_STATEMENT_OR_NONE);
    program2->makeNewSeq()->appendNonTerminalSymbol(NS_STATEMENT);
    program2->makeEmptySeq();
    auto *program3 = ruleSet->makeNewRule(NS_PROGRAM_BODY);
    program3->makeNewSeq()->appendNonTerminalSymbol(NS_FUNC);
    program3->makeNewSeq()->appendNonTerminalSymbol(NS_STATEMENT);
    program3->makeEmptySeq();
    auto *lineEnd = ruleSet->makeNewRule(NS_LINE_END);
    lineEnd->makeNewSeq()->appendTerminalSymbol(";");
    lineEnd->makeNewSeq()->appendTerminalSymbol(TokenType::eol);

    // 增加program对多条statement的识别
    auto *program4 = ruleSet->makeNewRule(NS_PROGRAM_STAR);
    program4->makeNewSeq()->appendNonTerminalSymbol(NS_PROGRAM);
    program4->makeEmptySeq();

    // statement 语法，包含了2个新产生式
    auto *statement = ruleSet->makeNewRule(NS_STATEMENT);
    statement->makeNewSeq()->appendTerminalSymbol(RW_IF)->appendNonTerminalSymbol(NS_EXPR)
            ->appendNonTerminalSymbol(NS_BLOCK)->appendNonTerminalSymbol(NS_STATEMENT_STAR);
    statement->makeNewSeq()->appendTerminalSymbol(RW_WHILE)->appendNonTerminalSymbol(NS_EXPR)
            ->appendNonTerminalSymbol(NS_BLOCK);
    statement->makeNewSeq()->appendNonTerminalSymbol(NS_SIMPLE);
    auto *statement2 = ruleSet->makeNewRule(NS_STATEMENT_STAR);
    statement2->makeNewSeq()->appendTerminalSymbol(RW_ELSE)->appendNonTerminalSymbol(NS_BLOCK);
    statement2->makeEmptySeq();

    // simple 语法，包含了1个新产生式
    auto *simple = ruleSet->makeNewRule(NS_SIMPLE);
    simple->makeNewSeq()->appendNonTerminalSymbol(NS_EXPR);

    // block 语法，包含了2个新产生式
    auto *block = ruleSet->makeNewRule(NS_BLOCK);
    block->makeNewSeq()->appendTerminalSymbol("{")->appendNonTerminalSymbol(NS_STATEMENT_OR_NONE)
            ->appendNonTerminalSymbol(NS_BLOCK_STAR)->appendTerminalSymbol("}");
    auto *block2 = ruleSet->makeNewRule(NS_BLOCK_STAR);
    block2->makeNewSeq()->appendNonTerminalSymbol(NS_LINE_END)->appendNonTerminalSymbol(NS_STATEMENT_OR_NONE)
            ->appendNonTerminalSymbol(NS_BLOCK_STAR);
    block2->makeEmptySeq();

    // expr 语法，包含了2个新产生式
    auto *expr = ruleSet->makeNewRule(NS_EXPR);
    expr->makeNewSeq()->appendNonTerminalSymbol(NS_FACTOR)->appendNonTerminalSymbol(NS_EXPR_STAR);
    auto *expr2 = ruleSet->makeNewRule(NS_EXPR_STAR);
    expr2->makeNewSeq()->appendTerminalSymbol(TokenType::op)->appendNonTerminalSymbol(NS_EXPR);
    expr2->makeEmptySeq();

    // factor 语法，包含了1个新产生式
    auto *factor = ruleSet->makeNewRule(NS_FACTOR);
    factor->makeNewSeq()->appendTerminalSymbol("-")->appendNonTerminalSymbol(NS_PRIMARY);
    factor->makeNewSeq()->appendNonTerminalSymbol(NS_PRIMARY);

    // primary 语法，包含了2个新产生式
    auto *primary = ruleSet->makeNewRule(NS_PRIMARY);
    primary->makeNewSeq()->appendTerminalSymbol("(")->appendNonTerminalSymbol(NS_EXPR)
            ->appendTerminalSymbol(")")->appendNonTerminalSymbol(NS_PRIMARY_STAR);
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::number);
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::identifier)->appendNonTerminalSymbol(NS_PRIMARY_STAR);
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::string);
    auto *primary2 = ruleSet->makeNewRule(NS_PRIMARY_STAR);
    primary2->makeNewSeq()->appendNonTerminalSymbol(NS_POSTFIX)->appendNonTerminalSymbol(NS_PRIMARY_STAR);
    primary2->makeEmptySeq();

    // param 语法，包含了1个新产生式
    auto *param = ruleSet->makeNewRule(NS_PARAM);
    param->makeNewSeq()->appendTerminalSymbol(TokenType::identifier);

    // params 语法，包含了2个新产生式
    auto *params = ruleSet->makeNewRule(NS_PARAMS);
    params->makeNewSeq()->appendNonTerminalSymbol(NS_PARAM)->appendNonTerminalSymbol(NS_PARAMS_STAR);
    auto *params2 = ruleSet->makeNewRule(NS_PARAMS_STAR);
    params2->makeNewSeq()->appendTerminalSymbol(",")->appendNonTerminalSymbol(NS_PARAMS);
    params2->makeEmptySeq();

    // param_list 语法，包含了2个新产生式
    auto *paramList = ruleSet->makeNewRule(NS_PARAM_LIST);
    paramList->makeNewSeq()->appendTerminalSymbol("(")->appendNonTerminalSymbol(NS_PARAM_LIST_OR_NONE)
    ->appendTerminalSymbol(")");
    auto *paramList2 = ruleSet->makeNewRule(NS_PARAM_LIST_OR_NONE);
    paramList2->makeNewSeq()->appendNonTerminalSymbol(NS_PARAMS);
    paramList2->makeEmptySeq();

    // func 语法，包含了1个新产生式
    auto *func = ruleSet->makeNewRule(NS_FUNC);
    func->makeNewSeq()->appendTerminalSymbol("function")->appendTerminalSymbol(TokenType::identifier)
    ->appendNonTerminalSymbol(NS_PARAM_LIST)->appendNonTerminalSymbol(NS_BLOCK);

    // args 语法，包含了2个新产生式
    auto *args = ruleSet->makeNewRule(NS_ARGS);
    args->makeNewSeq()->appendNonTerminalSymbol(NS_EXPR)->appendNonTerminalSymbol(NS_ARGS_STAR);
    auto *args2 = ruleSet->makeNewRule(NS_ARGS_STAR);
    args2->makeNewSeq()->appendTerminalSymbol(",")->appendNonTerminalSymbol(NS_ARGS);
    args2->makeEmptySeq();

    // postfix 语法，包含了2个新产生式
    auto *postfix = ruleSet->makeNewRule(NS_POSTFIX);
    postfix->makeNewSeq()->appendTerminalSymbol("(")->appendNonTerminalSymbol(NS_POSTFIX_OR_NONE)
    ->appendTerminalSymbol(")");
    auto *postfixOrNone = ruleSet->makeNewRule(NS_POSTFIX_OR_NONE);
    postfixOrNone->makeNewSeq()->appendNonTerminalSymbol(NS_ARGS);
    postfixOrNone->makeEmptySeq();

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
