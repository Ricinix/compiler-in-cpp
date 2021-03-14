//
// Created by laugh on 2021/3/14.
//

#ifndef DESIGN_1_OPNODEFETCHARR_H
#define DESIGN_1_OPNODEFETCHARR_H

#include "ASTNode.h"

class OpNodeFetchArr : public ASTList {
private:
    ASTNode *arrName;
    ASTNode *index;

    OpNodeFetchArr(ASTNode *arrNameNode, ASTNode *indexNode);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        ASTNode *arrName;
        ASTNode *index;
    public:
        void setArrName(ASTNode *arrNameNode);

        void setIndexNode(ASTNode *indexNode);

        OpNodeFetchArr *build();
    };
};


#endif //DESIGN_1_OPNODEFETCHARR_H
