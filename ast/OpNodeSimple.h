//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODESIMPLE_H
#define DESIGN_1_OPNODESIMPLE_H

#include "ASTNode.h"

class OpNodeSimple : public ASTList {
private:
    ASTNode *simpleStmt;

    bool isReturnStmt;

    explicit OpNodeSimple(ASTNode *simpleStmtNode, bool isReturn);

public:

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        ASTNode *simpleStmt = nullptr;
        bool isReturnStmt = false;
    public:
        void setSimpleStmt(ASTNode *node);

        void setReturnStmt(bool isReturn);

        OpNodeSimple *build();
    };
};


#endif //DESIGN_1_OPNODESIMPLE_H
