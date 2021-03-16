//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DEFINENODEOBJECT_H
#define DESIGN_1_DEFINENODEOBJECT_H

#include "ASTNode.h"
#include "DefineNodeDomain.h"
#include "DecorateNodeMethod.h"

class DefineNodeObject : public ASTList {
private:
    ASTNode *className;

    ASTNode *extendObj;

    std::vector<DefineNodeDomain *> domainSet;

    std::vector<DecorateNodeMethod *> methodSet;

    DefineNodeObject(ASTNode *name, ASTNode *extendNode, std::vector<DefineNodeDomain *> &domains,
                     std::vector<DecorateNodeMethod *> &methods);

protected:
    DefineNodeObject();

public:

    std::string toString() const override;

    void genCode(IoUtil &ioUtil) override;

    virtual void addDomain(DefineNodeDomain *domain);

    virtual void addMethod(DecorateNodeMethod *method);

    class Builder {
    private:
        ASTNode *className;
        ASTNode *extendObj = nullptr;
        std::vector<DefineNodeDomain *> domainSet;
        std::vector<DecorateNodeMethod *> methodSet;
    public:
        void setClassName(ASTNode *name);

        void setExtendObj(ASTNode *extendNode);

        void addDomain(DefineNodeDomain *domain);

        void addMethod(DecorateNodeMethod *method);

        DefineNodeObject *build();

    };

};


#endif //DESIGN_1_DEFINENODEOBJECT_H
