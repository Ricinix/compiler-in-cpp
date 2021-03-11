//
// Created by laugh on 2020/12/29.
//

#ifndef DESIGN_1_OPNODEBINARYEXPR_H
#define DESIGN_1_OPNODEBINARYEXPR_H

#include "ASTNode.h"
#include <vector>

class OpNodeBinaryExpr : public ASTList {
private:
    ASTNode *left;
    ASTNode *right;
    Token *token;

    OpNodeBinaryExpr(ASTNode *leftNode, ASTNode *rightNode, Token *t);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        ASTNode *left;
        ASTNode *right;
        Token *opToken;
    public:
        void setLeftNode(ASTNode *leftNode);

        void setRightNode(ASTNode *rightNode);

        void setToken(Token *t);

        OpNodeBinaryExpr *build();
    };
};


#endif //DESIGN_1_OPNODEBINARYEXPR_H
