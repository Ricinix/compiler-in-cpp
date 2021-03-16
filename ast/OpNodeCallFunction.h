//
// Created by laugh on 2021/3/14.
//

#ifndef DESIGN_1_OPNODECALLFUNCTION_H
#define DESIGN_1_OPNODECALLFUNCTION_H

#include "ASTNode.h"

class OpNodeCallFunction : public ASTList {
private:
    ASTNode *functionName;
    std::vector<ASTNode *> args;

    OpNodeCallFunction(std::vector<ASTNode *> &argList, ASTNode *funcName);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    class Builder {
    private:
        ASTNode *functionName;
        std::vector<ASTNode *> args;
    public:
        void addArg(ASTNode *arg);

        void setFunctionName(ASTNode *funcName);

        OpNodeCallFunction *build();
    };
};


#endif //DESIGN_1_OPNODECALLFUNCTION_H
