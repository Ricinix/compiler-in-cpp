//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODEBLOCK_H
#define DESIGN_1_OPNODEBLOCK_H

#include "ASTNode.h"

class OpNodeBlock : public ASTList {
public:
    explicit OpNodeBlock(const std::vector<ASTNode *> &v);

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        std::vector<ASTNode *> stmtSet;
    public:
        void appendChild(ASTNode *node);

        OpNodeBlock *build();
    };
};


#endif //DESIGN_1_OPNODEBLOCK_H
