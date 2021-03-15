//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_DEFINENODEDOMAIN_H
#define DESIGN_1_DEFINENODEDOMAIN_H

#include "ASTNode.h"

class DefineNodeDomain : public ASTList {
private:
    bool isStatic;
    ASTNode *initStmt;

    DefineNodeDomain(ASTNode *initStmtNode, bool isStaticDomain);

public:

    void genCode(IoUtil &ioUtil) override;

    std::string toString() const override;

    class Builder {
    private:
        bool isStatic;
        ASTNode *initStmt;
    public:
        void setInitStatement(ASTNode *stmt);

        void setStaticDomain(bool isStaticDomain);

        DefineNodeDomain *build();
    };
};


#endif //DESIGN_1_DEFINENODEDOMAIN_H
