//
// Created by laugh on 2021/3/3.
//

#ifndef DESIGN_1_OPNODEIF_H
#define DESIGN_1_OPNODEIF_H

#include "ASTNode.h"
#include "OpNodeElse.h"

class OpNodeIf : public ASTList {
private:
    ASTNode *condition;
    ASTNode *runBody;
    ASTNode *elsePart;

    OpNodeIf(ASTNode *conditionNode, ASTNode *runBodyNode, ASTNode *elseNode);

public:

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    class Builder {
    private:
        ASTNode *condition;
        ASTNode *runBody;
        ASTNode *elsePart;
    public:
        void setCondition(ASTNode *node);

        void setRunBody(ASTNode *node);

        void setElsePart(ASTNode *node);

        OpNodeIf *build();
    };
};


#endif //DESIGN_1_OPNODEIF_H
