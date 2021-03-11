//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DEFINENODEOBJECT_H
#define DESIGN_1_DEFINENODEOBJECT_H

#include "ASTNode.h"

class DefineNodeObject : public ASTList {
private:
    std::string className;

    std::vector<ASTNode *> domainSet;

    std::vector<ASTNode *> functionSet;

    DefineNodeObject(const std::string &name, std::vector<ASTNode *> &domains, std::vector<ASTNode *> &functions);

public:

    ~DefineNodeObject() override;

    std::string toString() const override;

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        std::string className;
        std::vector<ASTNode *> domainSet;
        std::vector<ASTNode *> functionSet;
    public:
        void setClassName(const std::string &name);

        void addDomain(ASTNode *domain);

        void addFunction(ASTNode *function);

        DefineNodeObject *build();

    };

};


#endif //DESIGN_1_DEFINENODEOBJECT_H
