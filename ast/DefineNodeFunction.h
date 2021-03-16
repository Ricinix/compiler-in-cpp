//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DEFINENODEFUNCTION_H
#define DESIGN_1_DEFINENODEFUNCTION_H

#include "ASTNode.h"

class DefineNodeFunction : public ASTList {
private:
    ASTNode *functionName;
    std::vector<ASTNode *> params;
    ASTNode *runBody;
    bool needOverride = false;

    DefineNodeFunction(ASTNode *funcName, std::vector<ASTNode *> &paramSet, ASTNode *runPart);

protected:
    DefineNodeFunction();

public:

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    int paramNum() const;

    void setNeedOverride(bool need);

    ASTNodeType getType() override;

    virtual std::string getHashMsg();

    class Builder {
    private:
        ASTNode *functionName;
        std::vector<ASTNode *> params;
        ASTNode *runBody;
    public:

        void setFunctionName(ASTNode *funcName);

        void addParam(ASTNode *param);

        void setRunBody(ASTNode *runPart);

        DefineNodeFunction *build();
    };
};


#endif //DESIGN_1_DEFINENODEFUNCTION_H
