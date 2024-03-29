//
// Created by laugh on 2020/12/31.
//

#include "Parser.h"
#include <ctime>
#include "../domain/exception.h"

Parser::Parser(RuleSet *ruleSet, Lexer *lexer) {
    rules = ruleSet;
    mLexer = lexer;
    hasGetParseTree = false;
    parseTree = new ParseTree();
}

Parser::~Parser() {
    if (!hasGetParseTree) {
        delete parseTree;
    }
}

void Parser::parse() {
    if (rules->ruleNum() <= 0) {
        Log::error("no rule");
        return;
    }
    int startTime = clock();
//    parseFromTop();
    parseFromTopWithStack();
    Log::warm("parse run time: " + std::to_string((float)(clock()-startTime)*1000/CLOCKS_PER_SEC));
}

void Parser::parseFromTop() {
    for (int i = 0; i < rules->ruleNum(); ++i) {
        Rule *rule = rules->getRule(i);
        auto *root = new ParseTreeNonLeaf(rule->getStartSymbol());
        parseTree->setRoot(root);
        if (recurParseFromTop(root)) {
            break;
        }
    }
//    Rule *rule = rules->getRule(0);
//    auto *root = new ParseTreeNonLeaf(rule->getStartSymbol());
//    parseTree->setRoot(root);
//    recurParseFromTop(root);
}

ParseTree *Parser::getParseTree() {
    hasGetParseTree = true;
    return parseTree;
}

bool Parser::recurParseFromTop(ParseTreeNode *node) {
    if (node->isLeaf()) {
        // 叶子节点则不需要再构造子树，所以该节点为根节点的子树构造成功
        Log::info(node->getNodeName() + "已是叶子节点");
        return true;
    }
    auto *rule = rules->getRule(node->getRuleItem());

    if (rule != nullptr) {
        for (int i = 0; i < rule->ruleSeqNum(); ++i) {
            bool seqSucceed = true; // 当前产生式是否正确
            auto *ruleSeq = rule->getRuleSeq(i);
            for (int j = 0; j < ruleSeq->ruleItemNum(); ++j) {
                auto *ruleItem = ruleSeq->getRuleItemByPos(j);
                if (ruleItem->getRuleItemType() == RuleItemType::NonTerminal) {
                    // 不是终结符则继续构造
                    auto *child = new ParseTreeNonLeaf(ruleItem);
                    node->setChild(j, child);
//                    node->appendChild(child);
                    if (!recurParseFromTop(child)) {
                        seqSucceed = false;
                        break;
                    }
                } else if (ruleItem->getRuleItemType() == RuleItemType::Empty) {
                    // ε则成功且保留当前token
                    auto *child = new ParseTreeLeaf(ruleItem, nullptr);
                    Log::info("增加新叶子节点: ε");
                    node->setChild(j, child);
//                    node->appendChild(child);
                } else if (ruleItem->matchToken(getNowToken())) {
                    // 终结符则停止
                    auto *child = new ParseTreeLeaf(ruleItem, getNowToken());
                    Log::info("增加新叶子节点: " + child->getNodeName());
                    node->setChild(j, child);
//                    node->appendChild(child);
                    nextToken();
                } else {
                    // 当前产生式识别错误，需要换个产生式
                    seqSucceed = false;
                    break;
                }
            }
            if (seqSucceed) {
                Log::info(node->getNodeName() + "子树构造成功");
                return true;
            } else {
                node->clearChildren();
            }
        }
    } else {
        Log::info(node->getNodeName() + "找不到该文法");
    }
    // 构造失败的原因：全部产生式都无法匹配上/无法找到对应的文法规则
    return false;
}

void Parser::nextToken() {
    nowToken = mLexer->read();
    Log::info(*nowToken);
}

Token *Parser::getNowToken() {
    if (nowToken == nullptr) {
        nextToken();
    }
    return nowToken;
}

void Parser::parseFromTopWithStack() {
    if (table == nullptr) {
        throw ParseException("can't parse in this way without stateTransitionTable");
    }
    Rule *rule = rules->getRule(0);
    auto *root = new ParseTreeNonLeaf(rule->getStartSymbol());
    parseTree->setRoot(root);
    symbolStack.push_back(root);
    while (!symbolStack.empty()) {
        auto *topNode = symbolStack[symbolStack.size() - 1];
        auto *topSymbol = topNode->getRuleItem();
        symbolStack.pop_back();
        if (topNode->isLeaf() && topSymbol->matchToken(getNowToken())) {
            // 加入终结符结点
            Log::info(topSymbol->getSymbolName() + " match " + getNowToken()->getText() + ", stack element num: "
                      + std::to_string(symbolStack.size()));
            topNode->setToken(getNowToken());
            nextToken();
        } else if (topNode->isLeaf() && topSymbol->getRuleItemType() == RuleItemType::Empty) {
            Log::info(topSymbol->getSymbolName() + " match " + getNowToken()->getText() + ", stack element num: "
                      + std::to_string(symbolStack.size()));
        } else if (topSymbol->getRuleItemType() == RuleItemType::Terminal) {
            throw ParseException("terminal error");
        } else {
            auto *ruleSeq = table->getRuleSeq(topSymbol, getNowToken());
            if (ruleSeq == nullptr) {
                throw ParseException("rule seq error");
            }
            // 加入非终结符结点
            for (int i = ruleSeq->ruleItemNum() - 1; i >= 0; --i) {
                auto *symbol = ruleSeq->getRuleItemByPos(i);
                if (symbol->getRuleItemType() == RuleItemType::NonTerminal) {
                    auto *child = new ParseTreeNonLeaf(symbol);
                    topNode->insertChild(0, child);
                    symbolStack.push_back(child);
                } else if (symbol->getRuleItemType() == RuleItemType::Empty) {
                    auto *child = new ParseTreeLeaf(symbol, nullptr);
                    Log::info("增加新叶子节点: ε");
                    topNode->insertChild(0, child);
                    symbolStack.push_back(child);
                } else if (symbol->getRuleItemType() == RuleItemType::End) {
                    Log::info("检测到: $");
                } else if (symbol->getRuleItemType() == RuleItemType::Terminal) {
                    auto *child = new ParseTreeLeaf(symbol, nullptr);
                    Log::info("增加新叶子节点: " + child->getNodeName());
                    topNode->insertChild(0, child);
                    symbolStack.push_back(child);
                }
            }
        }
    }
}

Parser::Parser(RuleSet *ruleSet, Lexer *lexer, StateTransitionTable *sst) {
    rules = ruleSet;
    table = sst;
    mLexer = lexer;
    hasGetParseTree = false;
    parseTree = new ParseTree();
}

