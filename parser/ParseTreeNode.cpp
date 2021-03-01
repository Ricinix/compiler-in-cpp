//
// Created by laugh on 2021/3/1.
//

#include "ParseTreeNode.h"

ParseTreeNode::ParseTreeNode(RuleItem *ruleItem) {
    symbol = ruleItem;
}

void ParseTreeNode::setFather(ParseTreeNode *node) {
    father = node;
}

ParseTreeNode *ParseTreeNode::getFather() {
    return father;
}

RuleItem *ParseTreeNode::getRuleItem() {
    return symbol;
}

ParseTreeNode::~ParseTreeNode() {
    for (auto &child : children) {
        delete child;
        child = nullptr;
    }
}

void ParseTreeNode::appendChildren(RuleSeq *ruleSeq) {
    for (int i = 0; i < ruleSeq->ruleItemNum(); ++i) {
        auto *ruleItem = ruleSeq->getRuleItemByPos(i);
        if (!ruleItem->isTerminal()) {
            children.push_back(new ParseTreeNonLeaf(ruleItem));
        } else {
            children.push_back(new ParseTreeLeaf(ruleItem));
        }
    }
}

void ParseTreeNode::appendChild(ParseTreeNode *node) {
    children.push_back(node);
}

void ParseTreeNode::setChild(int pos, ParseTreeNode *node) {
    if (children[pos] != nullptr) {
        delete children[pos];
    }
    children[pos] = node;
}

ParseTreeNode *ParseTreeNode::getChild(int pos) {
    return children[pos];
}

int ParseTreeNode::childNum() {
    return children.size();
}

void ParseTreeNode::clearChildren() {
    children.clear();
}

bool ParseTreeNode::isLeaf() {
    return false;
}


ParseTreeLeaf::ParseTreeLeaf(RuleItem *ruleItem) : ParseTreeNode(ruleItem) {

}

bool ParseTreeLeaf::isLeaf() {
    return true;
}

ParseTreeNonLeaf::ParseTreeNonLeaf(RuleItem *ruleItem) : ParseTreeNode(ruleItem) {

}

bool ParseTreeNonLeaf::isLeaf() {
    return true;
}
