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

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    void addDefineNode(ASTNode *node);

    int defineNum();

    ASTNode *getDefineNum(int i);

    void addStmtNode(ASTNode *node);

    int stmtNum();

    ASTNode *getStmt(int i);

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
