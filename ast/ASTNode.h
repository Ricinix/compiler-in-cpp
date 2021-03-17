//
// Created by laugh on 2020/12/24.
//

#ifndef DESIGN_1_ASTNODE_H
#define DESIGN_1_ASTNODE_H

#include <vector>
#include <string>
#include <memory>
#include "../lexer/Token.h"
#include "../util/IoUtil.h"

class ASTNode {
private:
    ASTNode *father = nullptr;
public:
    void setFather(ASTNode *node);

    ASTNode *getFather();

    virtual void insert(int i, ASTNode *node);

    virtual void append(ASTNode *node);

    virtual void removeAndDelete(int i);

    virtual void removeAndDelete(ASTNode *node);

    virtual void remove(int i);

    virtual void remove(ASTNode *node);

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
    virtual std::unique_ptr<ASTNode> work();

    virtual void genCode(IoUtil &ioUtil);

    virtual ASTNodeType getType();
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

    std::unique_ptr<ASTNode> work() override;

    void genCode(IoUtil &ioUtil) override;

    ASTNodeType getType() override;
};

/**
 * 非叶子节点
 */
class ASTList : public ASTNode {
protected:
    std::vector<ASTNode *> children;

    void addChild(ASTNode *node);

public:
    explicit ASTList(const std::vector<ASTNode *> &v);

    ASTList() = default;

    ~ASTList() override;

    ASTNode *child(int i) override;

    void insert(int i, ASTNode *node) override;

    void append(ASTNode *node) override;

    void removeAndDelete(int i) override;

    void removeAndDelete(ASTNode *node) override;

    void remove(int i) override;

    void remove(ASTNode *node) override;

    int numChildren() const override;

    std::string location() const override;

    std::string toString() const override;

    friend std::ostream &operator<<(std::ostream &os, const ASTList &astList);

    std::unique_ptr<ASTNode> work() override;

    void genCode(IoUtil &ioUtil) override;

    ASTNodeType getType() override;
};


#endif //DESIGN_1_ASTNODE_H
