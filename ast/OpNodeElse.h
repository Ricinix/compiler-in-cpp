//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_OPNODEELSE_H
#define DESIGN_1_OPNODEELSE_H

#include "ASTNode.h"

class OpNodeElse : public ASTList {
private:
    ASTNode *runBody;
public:
    explicit OpNodeElse(ASTNode *runBodyNode);

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        ASTNode *runBody;
    public:
        void setRunBody(ASTNode *runBodyNode);

        OpNodeElse *build();
    };
};


#endif //DESIGN_1_OPNODEELSE_H
