//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DECORATENODEPRIMARY_H
#define DESIGN_1_DECORATENODEPRIMARY_H

#include "ASTNode.h"

class DecorateNodePrimary : public ASTList {
private:
    ASTNode *expr;
public:
    explicit DecorateNodePrimary(ASTNode *exprNode);

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        ASTNode *expr;
    public:
        void setExprNode(ASTNode *exprNode);

        DecorateNodePrimary *build();
    };

};


#endif //DESIGN_1_DECORATENODEPRIMARY_H
