//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_PARSETREENODE_H
#define DESIGN_1_PARSETREENODE_H

#include <vector>
#include "../rule/RuleSeq.h"
#include "../ast/ASTNode.h"

/**
 * 语法分析树的基类
 */
class ParseTreeNode {
protected:
    ParseTreeNode *father = nullptr;
    std::vector<ParseTreeNode *> children;
    RuleItem *symbol;
    Token *token;
public:
    explicit ParseTreeNode(RuleItem *ruleItem);

    ParseTreeNode(RuleItem *ruleItem, Token *token_p);

    ~ParseTreeNode();

    void setFather(ParseTreeNode *node);

    ParseTreeNode *getFather();

    void appendChild(ParseTreeNode *node);

    void setChild(int pos, ParseTreeNode *node);

    ParseTreeNode *getChild(int pos);

    int childNum();

    void clearChildren();

    RuleItem *getRuleItem();

    virtual bool isLeaf();

    Token *getToken();

    virtual std::string getNodeName() const;

    virtual ASTNode *toASTNode();

};

class ParseTreeLeaf : public ParseTreeNode {
public:
    explicit ParseTreeLeaf(RuleItem *ruleItem);

    ParseTreeLeaf(RuleItem *ruleItem, Token *token_p);

    bool isLeaf() override;

    std::string getNodeName() const override;

    ASTNode *toASTNode() override;
};

class ParseTreeNonLeaf : public ParseTreeNode {
private:
    ASTNode* parseChildDirectly();
public:
    explicit ParseTreeNonLeaf(RuleItem *ruleItem);

    bool isLeaf() override;

    std::string getNodeName() const override;

    ASTNode *toASTNode() override;
};

#endif //DESIGN_1_PARSETREENODE_H
