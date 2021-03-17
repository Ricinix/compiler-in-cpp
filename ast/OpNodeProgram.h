//
// Created by laugh on 2021/3/3.
//

#ifndef DESIGN_1_OPNODEPROGRAM_H
#define DESIGN_1_OPNODEPROGRAM_H

#include "ASTNode.h"

/**
 * 连续执行多个独立语句
 */
class OpNodeProgram : public ASTList {
private:
    std::vector<ASTNode *> defineList;
    std::vector<ASTNode *> stmtList;

    static bool isDefineNode(ASTNode *node);

    explicit OpNodeProgram(const std::vector<ASTNode *> &v);

    void removeChildNoDelete(ASTNode *node);

    void addDefineNode(ASTNode *node);

    void addStmtNode(ASTNode *node);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    int defineNum();

    ASTNode *getDefineNum(int i);

    int stmtNum();

    ASTNode *getStmt(int i);

    void addNode(ASTNode *node);

    void remove(ASTNode *node) override;

    void removeAndDelete(ASTNode *node) override;

    /**
     * 该方法没有判断是否重复定义
     * @param i
     * @param node
     */
    void insertDefineNode(int i, ASTNode *node);

    class Builder {
    private:
        std::vector<ASTNode *> programSet;
    public:
        void appendChild(ASTNode *node);

        OpNodeProgram *build();
    };
};


#endif //DESIGN_1_OPNODEPROGRAM_H
