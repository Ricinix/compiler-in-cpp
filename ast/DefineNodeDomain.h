//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DEFINENODEDOMAIN_H
#define DESIGN_1_DEFINENODEDOMAIN_H

#include "ASTNode.h"

class DefineNodeDomain : public ASTList {
private:
    VisibleType type;
    std::string name;
    ASTNode* initStmt;
    DefineNodeDomain(VisibleType objType, const std::string &objName, ASTNode* initStmtNode);
public:

    VisibleType getVisibleType();

    std::string getName();

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        VisibleType type;
        std::string name;
        ASTNode* initStmt;
    public:
        void setVisibleType(VisibleType objType);
        void setName(const std::string &objName);
        void setInitStatement(ASTNode *stmt);
        DefineNodeDomain* build();
    };
};


#endif //DESIGN_1_DEFINENODEDOMAIN_H
