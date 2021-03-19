//
// Created by laugh on 2021/3/1.
//

#ifndef DESIGN_1_PARSETREENODE_H
#define DESIGN_1_PARSETREENODE_H

#include <vector>
#include "../rule/RuleSeq.h"
#include "../ast/ASTNode.h"
#include "../ast/DefineNodeObject.h"

/**
 * 语法分析树的基类
 */
class ParseTreeNode {
protected:
    ParseTreeNode *father = nullptr;
    RuleItem *symbol;
    Token *token;
public:
    explicit ParseTreeNode(RuleItem *ruleItem);

    ParseTreeNode(RuleItem *ruleItem, Token *token_p);

    ~ParseTreeNode();

    void setFather(ParseTreeNode *node);

    ParseTreeNode *getFather();

    Token *getToken();

    void setToken(Token *t);

    RuleItem *getRuleItem();

    virtual void appendChild(ParseTreeNode *node);

    virtual void setChild(int pos, ParseTreeNode *node);

    virtual void insertChild(int pos, ParseTreeNode *node);

    virtual ParseTreeNode *getChild(int pos);

    virtual int childNum();

    virtual void clearChildren();

    virtual bool isLeaf();

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
    std::vector<ParseTreeNode *> children;

    void checkChildNum(int correctNum);

    ASTNode *parseChildDirectly();

    static ASTNode *parsePostfixNode(ASTNode *prefixNode, ParseTreeNode *targetNode);

    static void castMember(DefineNodeObject::Builder &builder, ASTNode *member);

public:
    explicit ParseTreeNonLeaf(RuleItem *ruleItem);

    ~ParseTreeNonLeaf();

    bool isLeaf() override;

    std::string getNodeName() const override;

    ASTNode *toASTNode() override;

    void appendChild(ParseTreeNode *node) override;

    void clearChildren() override;

    ParseTreeNode * getChild(int pos) override;

    void insertChild(int pos, ParseTreeNode *node) override;

    void setChild(int pos, ParseTreeNode *node) override;

    int childNum() override;
};

#endif //DESIGN_1_PARSETREENODE_H
