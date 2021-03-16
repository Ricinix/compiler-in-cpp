//
// Created by laugh on 2021/3/10.
//

#ifndef DESIGN_1_OPNODEWHILE_H
#define DESIGN_1_OPNODEWHILE_H

#include "ASTNode.h"

class OpNodeWhile : public ASTList {
private:
    ASTNode *condition;
    ASTNode *runBody;

    OpNodeWhile(ASTNode *conditionNode, ASTNode *runBodyNode);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    class Builder {
    private:
        ASTNode *condition;
        ASTNode *runBody;
    public:
        void setCondition(ASTNode *node);

        void setRunBody(ASTNode *node);

        OpNodeWhile *build();
    };
};


#endif //DESIGN_1_OPNODEWHILE_H
