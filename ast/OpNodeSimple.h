//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODESIMPLE_H
#define DESIGN_1_OPNODESIMPLE_H

#include "ASTNode.h"

class OpNodeSimple : public ASTList {
private:
    ASTNode *simpleStmt;
public:
    explicit OpNodeSimple(ASTNode *simpleStmtNode);

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        ASTNode *simpleStmt;
    public:
        void setSimpleStmt(ASTNode *node);

        OpNodeSimple *build();
    };
};


#endif //DESIGN_1_OPNODESIMPLE_H
