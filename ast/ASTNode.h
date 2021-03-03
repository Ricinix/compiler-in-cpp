//
// Created by laugh on 2020/12/24.
//

#ifndef DESIGN_1_ASTNODE_H
#define DESIGN_1_ASTNODE_H

#include <vector>
#include <string>
#include <memory>
#include "../lexer/Token.h"
#include "../rule/Operator.h"

class ASTNode {

public:
    virtual ASTNode *child(int i);

    virtual int numChildren() const;

    virtual std::string location() const;

    virtual std::string toString() const;

    virtual ~ASTNode() = default;

    /**
     * 若未进行任何操作，或不需要返回值，则返回空指针
     * @param op
     * @param node
     * @return
     */
    virtual std::unique_ptr<ASTNode> work(Operator *op, ASTNode *node);
};

/**
 * 叶子节点
 */
class ASTLeaf : public ASTNode {
protected:
    Token *token_ptr;
public:
    explicit ASTLeaf(Token *token_p);

    ~ASTLeaf() override = default;

    ASTNode *child(int i) override;

    int numChildren() const override;

    std::string location() const override;

    std::string toString() const override;

    Token *token();

    friend std::ostream &operator<<(std::ostream &os, const ASTLeaf &astLeaf);
};

/**
 * 非叶子节点
 */
class ASTList : public ASTNode {
protected:
    std::vector<ASTNode *> children;
public:
    explicit ASTList(const std::vector<ASTNode *> &v);

    ASTList() = default;

    ~ASTList() override;

    ASTNode *child(int i) override;

    int numChildren() const override;

    std::string location() const override;

    std::string toString() const override;

    friend std::ostream &operator<<(std::ostream &os, const ASTList &astList);
};


#endif //DESIGN_1_ASTNODE_H
