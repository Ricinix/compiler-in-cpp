//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_PARSETREENODE_H
#define DESIGN_1_PARSETREENODE_H

#include <vector>
#include "../rule/RuleSeq.h"

/**
 * 语法分析树的基类
 */
class ParseTreeNode {
protected:
    ParseTreeNode *father = nullptr;
    std::vector<ParseTreeNode *> children;
    RuleItem *symbol;
public:
    explicit ParseTreeNode(RuleItem *ruleItem);

    ~ParseTreeNode();

    void setFather(ParseTreeNode* node);

    ParseTreeNode* getFather();

    void appendChildren(RuleSeq* ruleSeq);

    void appendChild(ParseTreeNode* node);

    void setChild(int pos, ParseTreeNode* node);

    ParseTreeNode* getChild(int pos);

    int childNum();

    void clearChildren();

    RuleItem* getRuleItem();

    virtual bool isLeaf();
};

class ParseTreeLeaf : public ParseTreeNode {
public:
    explicit ParseTreeLeaf(RuleItem *ruleItem);
    bool isLeaf() override;
};

class ParseTreeNonLeaf : public ParseTreeNode {
public:
    explicit ParseTreeNonLeaf(RuleItem *ruleItem);
    bool isLeaf() override;
};

#endif //DESIGN_1_PARSETREENODE_H
