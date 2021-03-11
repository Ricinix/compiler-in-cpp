//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODESIMPLE_H
#define DESIGN_1_OPNODESIMPLE_H

#include "ASTNode.h"

class OpNodeSimple : public ASTList {
private:
    ASTNode *simpleStmt;

    explicit OpNodeSimple(ASTNode *simpleStmtNode);

public:

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        ASTNode *simpleStmt;
    public:
        void setSimpleStmt(ASTNode *node);

        OpNodeSimple *build();
    };
};


#endif //DESIGN_1_OPNODESIMPLE_H
