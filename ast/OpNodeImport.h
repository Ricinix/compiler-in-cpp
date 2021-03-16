//
// Created by laugh on 2021/3/15.
//

#ifndef DESIGN_1_OPNODEIMPORT_H
#define DESIGN_1_OPNODEIMPORT_H

#include "ASTNode.h"

/**
 * TODO 此结点需要在生成代码前解析并去掉
 */
class OpNodeImport : public ASTList {
private:
    ASTNode *path;

    explicit OpNodeImport(ASTNode *pathNode);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    std::string getPathInStr();

    class Builder {
    private:
        ASTNode *path;
    public:
        void setPath(ASTNode *pathNode);

        OpNodeImport *build();
    };
};


#endif //DESIGN_1_OPNODEIMPORT_H
