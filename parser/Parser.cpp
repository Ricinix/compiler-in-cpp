//
// Created by laugh on 2020/12/31.
//

#include "Parser.h"

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
    parseFromTop();
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

}

ParseTree *Parser::getParseTree() {
    hasGetParseTree = true;
    return parseTree;
}

bool Parser::recurParseFromTop(ParseTreeNode* node) {
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
                    child->setFather(node);
//                    node->setChild(j, child);
                    node->appendChild(child);
                    if (!recurParseFromTop(child)) {
                        seqSucceed = false;
                        break;
                    }
                } else if (ruleItem->getRuleItemType() == RuleItemType::Empty) {
                    // ε则成功且保留当前token
                    auto *child = new ParseTreeLeaf(ruleItem, nullptr);
                    Log::info("增加新叶子节点: ε");
                    child->setFather(node);
                    node->appendChild(child);
                } else if (ruleItem->matchToken(getNowToken())){
                    // 终结符则停止
                    auto *child = new ParseTreeLeaf(ruleItem, getNowToken());
                    Log::info("增加新叶子节点: " + child->getNodeName());
                    child->setFather(node);
                    node->appendChild(child);
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
//    Log::info(node->getRuleItem()->getSymbolName() + "构建失败");
    return false;
}

void Parser::nextToken() {
    nowToken = mLexer->read();
    Log::info("读取Token: " + nowToken->getText());
}

Token *Parser::getNowToken() {
    if (nowToken == nullptr) {
        nextToken();
    }
    return nowToken;
}

