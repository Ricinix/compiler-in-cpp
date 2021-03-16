//
// Created by laugh on 2021/3/15.
//

#ifndef DESIGN_1_DECORATENODEMETHOD_H
#define DESIGN_1_DECORATENODEMETHOD_H

#include "ASTNode.h"
#include "DefineNodeFunction.h"

class DecorateNodeMethod : public ASTList {
private:
    bool isStatic;
    DefineNodeFunction *func;

protected:
    DecorateNodeMethod(DefineNodeFunction *funcNode, bool isStaticMethod);

public:
    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    ASTNodeType getType() override;

    virtual std::string getHashMsg() const;

    std::string getMethodName();

    int getParamNum();

    class Builder {
    private:
        bool isStatic;
        DefineNodeFunction *func;
    public:
        void setStatic(bool isStaticMethod);

        void setFunc(DefineNodeFunction *funcNode);

        DecorateNodeMethod *build();
    };
};


#endif //DESIGN_1_DECORATENODEMETHOD_H
