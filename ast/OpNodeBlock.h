//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODEBLOCK_H
#define DESIGN_1_OPNODEBLOCK_H

#include "ASTNode.h"

class OpNodeBlock : public ASTList {
private:

    explicit OpNodeBlock(const std::vector<ASTNode *> &v);

public:

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    class Builder {
    private:
        std::vector<ASTNode *> stmtSet;
    public:
        void appendChild(ASTNode *node);

        OpNodeBlock *build();
    };
};


#endif //DESIGN_1_OPNODEBLOCK_H
