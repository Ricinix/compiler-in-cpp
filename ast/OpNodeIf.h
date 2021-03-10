//
// Created by laugh on 2021/3/3.
//

#ifndef DESIGN_1_OPNODEIF_H
#define DESIGN_1_OPNODEIF_H

#include "ASTNode.h"

class OpNodeIf : public ASTList {
private:
    ASTNode *condition;
    ASTNode *runBody;
    OpNodeIf(ASTNode* conditionNode, ASTNode* runBodyNode);
public:
    std::unique_ptr<ASTNode> work() override;
    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        ASTNode *condition;
        ASTNode *runBody;
    public:
        void setCondition(ASTNode* node);
        void setRunBody(ASTNode* node);
        OpNodeIf* build();
    };
};


#endif //DESIGN_1_OPNODEIF_H
