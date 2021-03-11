//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODESINGLEEXPR_H
#define DESIGN_1_OPNODESINGLEEXPR_H

#include "ASTNode.h"

class OpNodeSingleExpr : public ASTList {
private:
    Token *token;
    ASTNode *factor;
public:
    OpNodeSingleExpr(ASTNode *factorNode, Token *opToken);

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        Token *opToken;
        ASTNode *factor;
    public:
        void setOpToken(Token *t);

        void setFactor(ASTNode *node);

        OpNodeSingleExpr *build();
    };
};


#endif //DESIGN_1_OPNODESINGLEEXPR_H
