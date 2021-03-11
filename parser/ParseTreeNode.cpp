//
// Created by laugh on 2021/3/1.
//

#include "ParseTreeNode.h"
#include "../ast/NumberLiteral.h"
#include "../ast/StringLiteral.h"
#include "../ast/Identifier.h"

ParseTreeNode::ParseTreeNode(RuleItem *ruleItem) {
    symbol = ruleItem;
    token = nullptr;
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

void ParseTreeNode::appendChild(ParseTreeNode *node) {
    node->setFather(this);
    children.push_back(node);
}

void ParseTreeNode::setChild(int pos, ParseTreeNode *node) {
    if (childNum() >= pos) {
        appendChild(node);
        return;
    }
    if (children[pos] != nullptr) {
        delete children[pos];
    }
    children[pos] = node;
    node->setFather(this);
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

ParseTreeNode::ParseTreeNode(RuleItem *ruleItem, Token *token_p) {
    symbol = ruleItem;
    token = token_p;
}

Token *ParseTreeNode::getToken() {
    return token;
}

std::string ParseTreeNode::getNodeName() const {
    return "";
}

ASTNode *ParseTreeNode::toASTNode() {
    return nullptr;
}


ParseTreeLeaf::ParseTreeLeaf(RuleItem *ruleItem, Token* token_p) : ParseTreeNode(ruleItem, token_p) {

}

bool ParseTreeLeaf::isLeaf() {
    return true;
}

ParseTreeLeaf::ParseTreeLeaf(RuleItem *ruleItem) : ParseTreeNode(ruleItem) {

}

std::string ParseTreeLeaf::getNodeName() const {
    if (token == nullptr) {
        return symbol->getSymbolName();
    }
    return token->getText();
}

ASTNode *ParseTreeLeaf::toASTNode() {
    if (getToken()->getTokenType() == TokenType::number) {
        return new NumberLiteral(getToken());
    } else if (getToken()->getTokenType() == TokenType::string) {
        return new StringLiteral(getToken());
    } else if (getToken()->getTokenType() == TokenType::identifier) {
        return new Identifier(getToken());
    }
    return nullptr;
}

ParseTreeNonLeaf::ParseTreeNonLeaf(RuleItem *ruleItem) : ParseTreeNode(ruleItem) {

}

bool ParseTreeNonLeaf::isLeaf() {
    return false;
}

std::string ParseTreeNonLeaf::getNodeName() const {
    return "NonLeaf: " + symbol->getSymbolName();
}

ASTNode *ParseTreeNonLeaf::toASTNode() {
    return ParseTreeNode::toASTNode();
}
