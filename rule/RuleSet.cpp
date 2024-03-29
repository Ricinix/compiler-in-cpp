//
// Created by laugh on 2021/3/1.
//

#include <sstream>
#include "RuleSet.h"
#include "../domain/exception.h"
#include "../util/Log.h"

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
    program3->makeNewSeq()->appendNonTerminalSymbol(NS_CLASS);
    program3->makeNewSeq()->appendNonTerminalSymbol(NS_FUNC);
    program3->makeNewSeq()->appendNonTerminalSymbol(NS_STATEMENT);
    program3->makeEmptySeq();
    auto *lineEnd = ruleSet->makeNewRule(NS_LINE_END);
    lineEnd->makeNewSeq()->appendTerminalSymbol(RW_SEMICOLON);
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

    // simple 语法，包含了2个新产生式
    auto *simple = ruleSet->makeNewRule(NS_SIMPLE);
    simple->makeNewSeq()->appendNonTerminalSymbol(NS_RETURN)->appendNonTerminalSymbol(NS_EXPR);
    auto *returnRule = ruleSet->makeNewRule(NS_RETURN);
    returnRule->makeNewSeq()->appendTerminalSymbol(RW_RETURN);
    returnRule->makeEmptySeq();

    // block 语法，包含了2个新产生式
    auto *block = ruleSet->makeNewRule(NS_BLOCK);
    block->makeNewSeq()->appendTerminalSymbol(RW_LEFT_BRACE)->appendNonTerminalSymbol(NS_STATEMENT_OR_NONE)
            ->appendNonTerminalSymbol(NS_BLOCK_STAR)->appendTerminalSymbol(RW_RIGHT_BRACE);
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

    // primary 语法，包含了6个新产生式
    auto *primary = ruleSet->makeNewRule(NS_PRIMARY);
    primary->makeNewSeq()->appendTerminalSymbol(RW_LEFT_SQUARE_BRACKET)->appendNonTerminalSymbol(NS_ELEMENTS_OR_NONE)
            ->appendTerminalSymbol(RW_RIGHT_SQUARE_BRACKET);
    primary->makeNewSeq()->appendTerminalSymbol(RW_LEFT_BRACKET)->appendNonTerminalSymbol(NS_EXPR)
            ->appendTerminalSymbol(RW_RIGHT_BRACKET)->appendNonTerminalSymbol(NS_PRIMARY_STAR);
    primary->makeNewSeq()->appendTerminalSymbol(TokenType::number)->appendNonTerminalSymbol(NS_DECIMALS);
    primary->makeNewSeq()->appendNonTerminalSymbol(NS_NEW)->appendTerminalSymbol(TokenType::identifier)
            ->appendNonTerminalSymbol(NS_PRIMARY_STAR);
    primary->makeNewSeq()->appendNonTerminalSymbol(NS_IMPORT_OR_NONE)->appendTerminalSymbol(TokenType::string);
    auto *primary2 = ruleSet->makeNewRule(NS_PRIMARY_STAR);
    primary2->makeNewSeq()->appendNonTerminalSymbol(NS_POSTFIX)->appendNonTerminalSymbol(NS_PRIMARY_STAR);
    primary2->makeEmptySeq();
    auto *decimals = ruleSet->makeNewRule(NS_DECIMALS);
    decimals->makeNewSeq()->appendTerminalSymbol(RW_DOT)->appendTerminalSymbol(TokenType::number);
    decimals->makeEmptySeq();
    auto *elementsOrNone = ruleSet->makeNewRule(NS_ELEMENTS_OR_NONE);
    elementsOrNone->makeNewSeq()->appendNonTerminalSymbol(NS_ELEMENTS);
    elementsOrNone->makeEmptySeq();
    auto *newOrNone = ruleSet->makeNewRule(NS_NEW);
    newOrNone->makeNewSeq()->appendTerminalSymbol(RW_NEW);
    newOrNone->makeEmptySeq();
    auto *importOrNone = ruleSet->makeNewRule(NS_IMPORT_OR_NONE);
    importOrNone->makeNewSeq()->appendTerminalSymbol(RW_IMPORT);
    importOrNone->makeEmptySeq();

    // param 语法，包含了1个新产生式
    auto *param = ruleSet->makeNewRule(NS_PARAM);
    param->makeNewSeq()->appendTerminalSymbol(TokenType::identifier);

    // params 语法，包含了2个新产生式
    auto *params = ruleSet->makeNewRule(NS_PARAMS);
    params->makeNewSeq()->appendNonTerminalSymbol(NS_PARAM)->appendNonTerminalSymbol(NS_PARAMS_STAR);
    auto *params2 = ruleSet->makeNewRule(NS_PARAMS_STAR);
    params2->makeNewSeq()->appendTerminalSymbol(RW_COMMA)->appendNonTerminalSymbol(NS_PARAMS);
    params2->makeEmptySeq();

    // param_list 语法，包含了2个新产生式
    auto *paramList = ruleSet->makeNewRule(NS_PARAM_LIST);
    paramList->makeNewSeq()->appendTerminalSymbol(RW_LEFT_BRACKET)->appendNonTerminalSymbol(NS_PARAM_LIST_OR_NONE)
            ->appendTerminalSymbol(RW_RIGHT_BRACKET);
    auto *paramList2 = ruleSet->makeNewRule(NS_PARAM_LIST_OR_NONE);
    paramList2->makeNewSeq()->appendNonTerminalSymbol(NS_PARAMS);
    paramList2->makeEmptySeq();

    // func 语法，包含了1个新产生式
    auto *func = ruleSet->makeNewRule(NS_FUNC);
    func->makeNewSeq()->appendTerminalSymbol(RW_FUNC)->appendTerminalSymbol(TokenType::identifier)
            ->appendNonTerminalSymbol(NS_PARAM_LIST)->appendNonTerminalSymbol(NS_BLOCK);

    // args 语法，包含了2个新产生式
    auto *args = ruleSet->makeNewRule(NS_ARGS);
    args->makeNewSeq()->appendNonTerminalSymbol(NS_EXPR)->appendNonTerminalSymbol(NS_ARGS_STAR);
    auto *args2 = ruleSet->makeNewRule(NS_ARGS_STAR);
    args2->makeNewSeq()->appendTerminalSymbol(RW_COMMA)->appendNonTerminalSymbol(NS_ARGS);
    args2->makeEmptySeq();

    // postfix 语法，包含了2个新产生式
    auto *postfix = ruleSet->makeNewRule(NS_POSTFIX);
    postfix->makeNewSeq()->appendTerminalSymbol(RW_DOT)->appendTerminalSymbol(TokenType::identifier);
    postfix->makeNewSeq()->appendTerminalSymbol(RW_LEFT_BRACKET)->appendNonTerminalSymbol(NS_POSTFIX_OR_NONE)
            ->appendTerminalSymbol(RW_RIGHT_BRACKET);
    postfix->makeNewSeq()->appendTerminalSymbol(RW_LEFT_SQUARE_BRACKET)->appendNonTerminalSymbol(NS_EXPR)
            ->appendTerminalSymbol(RW_RIGHT_SQUARE_BRACKET);
    auto *postfixOrNone = ruleSet->makeNewRule(NS_POSTFIX_OR_NONE);
    postfixOrNone->makeNewSeq()->appendNonTerminalSymbol(NS_ARGS);
    postfixOrNone->makeEmptySeq();

    // class 语法，包含了2个新产生式
    auto *classRule = ruleSet->makeNewRule(NS_CLASS);
    classRule->makeNewSeq()->appendTerminalSymbol(RW_CLASS)->appendTerminalSymbol(TokenType::identifier)
            ->appendNonTerminalSymbol(NS_EXTENDS)->appendNonTerminalSymbol(NS_CLASS_BODY);
    auto *extends = ruleSet->makeNewRule(NS_EXTENDS);
    extends->makeNewSeq()->appendTerminalSymbol(RW_EXTENDS)->appendTerminalSymbol(TokenType::identifier);
    extends->makeEmptySeq();

    // class_body 语法，包含了3个新产生式
    auto *classBody = ruleSet->makeNewRule(NS_CLASS_BODY);
    classBody->makeNewSeq()->appendTerminalSymbol(RW_LEFT_BRACE)->appendNonTerminalSymbol(NS_MEMBER_OR_NONE)
            ->appendNonTerminalSymbol(NS_CLASS_BODY_STAR)->appendTerminalSymbol(RW_RIGHT_BRACE);
    auto *memberOrNone = ruleSet->makeNewRule(NS_MEMBER_OR_NONE);
    memberOrNone->makeNewSeq()->appendNonTerminalSymbol(NS_MEMBER);
    memberOrNone->makeEmptySeq();
    auto *classBodyStar = ruleSet->makeNewRule(NS_CLASS_BODY_STAR);
    classBodyStar->makeNewSeq()->appendNonTerminalSymbol(NS_LINE_END)->appendNonTerminalSymbol(NS_MEMBER_OR_NONE)
            ->appendNonTerminalSymbol(NS_CLASS_BODY_STAR);
    classBodyStar->makeEmptySeq();

    // member 语法，包含了3个新产生式
    auto *member = ruleSet->makeNewRule(NS_MEMBER);
    member->makeNewSeq()->appendNonTerminalSymbol(NS_STATIC_OR_NONE)->appendNonTerminalSymbol(NS_MEMBER_STAR);
    auto *staticOrNone = ruleSet->makeNewRule(NS_STATIC_OR_NONE);
    staticOrNone->makeNewSeq()->appendTerminalSymbol(RW_STATIC);
    staticOrNone->makeEmptySeq();
    auto *memberStar = ruleSet->makeNewRule(NS_MEMBER_STAR);
    memberStar->makeNewSeq()->appendNonTerminalSymbol(NS_FUNC);
    memberStar->makeNewSeq()->appendNonTerminalSymbol(NS_SIMPLE);

    // elements 语法，包含了2个新产生式
    auto *elements = ruleSet->makeNewRule(NS_ELEMENTS);
    elements->makeNewSeq()->appendNonTerminalSymbol(NS_EXPR)->appendNonTerminalSymbol(NS_ELEMENTS_STAR);
    auto *elementsStar = ruleSet->makeNewRule(NS_ELEMENTS_STAR);
    elementsStar->makeNewSeq()->appendTerminalSymbol(RW_COMMA)->appendNonTerminalSymbol(NS_ELEMENTS);
    elementsStar->makeEmptySeq();

    return ruleSet;
}

int RuleSet::ruleNum() {
    return ruleSet.size();
}

Rule *RuleSet::getRule(int i) {
    return ruleSet[i];
}

Rule *RuleSet::getRule(const std::string &startSymbolName) {
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

FirstSet *RuleSet::getFirstSet(RuleItem *ruleItem) {
    auto first = firstSet.find(getHashCode(ruleItem));
    if (first != firstSet.end()) {
        return first->second;
    }
    return initFirstSet(ruleItem);
}

FollowSet *RuleSet::getFollowSet(RuleItem *ruleItem) {
    if (ruleItem->getRuleItemType() != RuleItemType::NonTerminal) {
        throw ParseException("can't get follow set from terminal symbol");
    }
    if (followSet.empty()) {
        initFollowSet();
    }
    auto follow = followSet.find(ruleItem->getSymbolName());
    if (follow != followSet.end()) {
        return follow->second;
    }
    throw ParseException("can't find " + ruleItem->getSymbolName() + "in follow set");
}

FirstSet *RuleSet::initFirstSet(RuleItem *ruleItem) {
    auto builder = FirstSet::Builder(ruleItem);
    findFirst(builder, ruleItem);
    auto *first = builder.build();
    firstSet[getHashCode(ruleItem)] = first;
    return first;
}

void RuleSet::initFollowSet() {
    bool hasAddNew = true;
    int round = 1;
    while (hasAddNew) {
        hasAddNew = false;
        Log::info("init follow set round " + std::to_string(round) + " start");
        for (auto &rule : ruleSet) {
            auto *startFollow = getFollowFromMap(rule->getStartSymbol());
            startFollow->addEndSymbol();
            for (int i = 0; i < rule->ruleSeqNum(); ++i) {
                auto *ruleSeq = rule->getRuleSeq(i);
                for (int j = 0; j < ruleSeq->ruleItemNum(); ++j) {
                    auto *symbol = ruleSeq->getRuleItemByPos(j);
                    if (symbol->getRuleItemType() != RuleItemType::NonTerminal) {
                        continue;
                    }
                    auto *symbolFollow = getFollowFromMap(symbol);
                    if (j == ruleSeq->ruleItemNum() - 1) {
                        // 在末尾，取头的follow
                        hasAddNew = hasAddNew || symbolFollow->concatSymbolSet(startFollow);
                    } else {
                        // 不在末尾
                        auto *first = getFirstSet(ruleSeq, j + 1, ruleSeq->ruleItemNum());;
                        hasAddNew = hasAddNew || symbolFollow->concatSymbolSet(first);
                        if (first->hasEmptySymbol()) {
                            hasAddNew = hasAddNew || symbolFollow->concatSymbolSet(startFollow);
                        }
                    }
                }
            }
            Log::info(*startFollow);
        }
        Log::info("init follow set round " + std::to_string(round++) + " end");
    }
}

bool RuleSet::findFirst(FirstSet::Builder &builder, RuleItem *ruleItem) {
    if (ruleItem->getRuleItemType() == RuleItemType::Terminal) {
        // 终结符
        builder.addTerminalSymbol(ruleItem);
        return false;
    }
    if (ruleItem->getRuleItemType() == RuleItemType::Empty) {
        // 空
        if (ruleItem == builder.getBelongSymbol()) {
            builder.addEmptySymbol();
        }
        return true;
    }
    // 非终结符
    auto *rule = getRule(ruleItem);
    bool hasEmpty = false;
    for (int i = 0; i < rule->ruleSeqNum(); ++i) {
        // 检查每个产生式
        auto *ruleSeq = rule->getRuleSeq(i);
        int emptyNum = 0;
        for (int j = 0; j < ruleSeq->ruleItemNum(); ++j) {
            // 检查产生式右边的每个符号
            auto *symbol = ruleSeq->getRuleItemByPos(j);
            if (findFirst(builder, symbol)) {
                ++emptyNum;
            } else {
                break;
            }
        }
        if (emptyNum == ruleSeq->ruleItemNum()) {
            hasEmpty = true;
            if (ruleItem == builder.getBelongSymbol()) {
                builder.addEmptySymbol();
            }
        }
    }
    return hasEmpty;
}

FirstSet *RuleSet::getFirstSet(RuleSeq *ruleSeq, int startIndex, int endIndex) {
    std::ostringstream fmt;
    for (int i = startIndex; i < endIndex; ++i) {
        auto *item = ruleSeq->getRuleItemByPos(i);
        fmt << getHashCode(item);
        if (i != endIndex - 1) {
            fmt << "_";
        }
    }
    auto firstPair = firstSet.find(fmt.str());
    if (firstPair != firstSet.end()) {
        return firstPair->second;
    }
    if (endIndex - startIndex == 1) {
        return getFirstSet(ruleSeq->getRuleItemByPos(startIndex));
    }
    auto builder = FirstSet::Builder(ruleSeq->getRuleItemByPos(startIndex));
    builder.setMultipleNum(endIndex - startIndex);
    for (int i = startIndex; i < endIndex; ++i) {
        auto *item = ruleSeq->getRuleItemByPos(i);
        if (item->getRuleItemType() == RuleItemType::NonTerminal) {
            // 非终结符
            auto *first = getFirstSet(item);
            builder.concatSymbolSet(first);
            if (!first->hasEmptySymbol()) {
                // 如果没有空则不需要继续往后查first集了
                break;
            }
            if (i == endIndex - 1) {
                builder.addEmptySymbol();
            }
        } else {
            // 终结符
            builder.addTerminalSymbol(item);
            break;
        }
    }
    auto *first = builder.build();
    firstSet[fmt.str()] = first;
    return first;
}

bool RuleSet::isLLOne() {
    for (auto &rule : ruleSet) {
        if (rule->ruleSeqNum() < 2) {
            continue;
        }
        for (int i = 0; i < rule->ruleSeqNum() - 1; ++i) {
            auto *seqOne = rule->getRuleSeq(i);
            Log::info("doing " + rule->getStartSymbol()->getSymbolName() + " " + std::to_string(i));
            auto *firstOne = getFirstSet(seqOne, 0, seqOne->ruleItemNum());
            for (int j = i + 1; j < rule->ruleSeqNum(); ++j) {
                Log::info("doing " + rule->getStartSymbol()->getSymbolName() + " " + std::to_string(j));
                auto *seqTwo = rule->getRuleSeq(j);
                auto *firstTwo = getFirstSet(seqTwo, 0, seqTwo->ruleItemNum());
                if (firstOne->cross(firstTwo)) {
                    Log::info(rule->getStartSymbol()->getSymbolName() + " " + std::to_string(i) + " and "
                              + std::to_string(j) + " is cross");
                    return false;
                }
                if (firstOne->hasEmptySymbol() && firstTwo->cross(getFollowSet(rule->getStartSymbol()))) {
                    Log::info(rule->getStartSymbol()->getSymbolName() + " " + std::to_string(i) + " is empty, "
                              + std::to_string(j) + " cross follow");
                    return false;
                } else if (firstTwo->hasEmptySymbol() && firstOne->cross(getFollowSet(rule->getStartSymbol()))) {
                    Log::info(rule->getStartSymbol()->getSymbolName() + " " + std::to_string(j) + " is empty, "
                              + std::to_string(i) + " cross follow");
                    return false;
                }
            }
        }
    }
    return true;
}

std::string RuleSet::getHashCode(RuleItem *ruleItem) {
    if (ruleItem->getRuleItemType() == RuleItemType::NonTerminal) {
        return ruleItem->getSymbolName();
    } else {
        return "T-" + ruleItem->getSymbolName();
    }
}

FollowSet *RuleSet::getFollowFromMap(RuleItem *ruleItem) {
    if (ruleItem->getRuleItemType() != RuleItemType::NonTerminal) {
        throw ParseException("can't generate follow set from terminal symbol");
    }
    auto pair = followSet.find(ruleItem->getSymbolName());
    if (pair != followSet.end()) {
        return pair->second;
    }
    auto *follow = new FollowSet(ruleItem);
    followSet[ruleItem->getSymbolName()] = follow;
    return follow;
}
