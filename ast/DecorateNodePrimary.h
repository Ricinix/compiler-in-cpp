//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DECORATENODEPRIMARY_H
#define DESIGN_1_DECORATENODEPRIMARY_H

#include "ASTNode.h"
/**
 * 用来装饰(expr)，打印括号用的
 */
class DecorateNodePrimary : public ASTList {
private:
    ASTNode *expr;

    explicit DecorateNodePrimary(ASTNode *exprNode);

public:

    ASTNodeType getType() override;

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        ASTNode *expr;
    public:
        void setExprNode(ASTNode *exprNode);

        DecorateNodePrimary *build();
    };

};


#endif //DESIGN_1_DECORATENODEPRIMARY_H
