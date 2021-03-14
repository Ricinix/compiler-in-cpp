//
// Created by laugh on 2021/3/14.
//

#ifndef DESIGN_1_NEWNODEOBJECT_H
#define DESIGN_1_NEWNODEOBJECT_H

#include "ASTNode.h"

class NewNodeObject : public ASTList {
private:
    ASTNode *objNameId;

    explicit NewNodeObject(ASTNode *objNameNode);

public:
    void genCode(IoUtil &ioUtil) override;
    std::string toString() const override;

    class Builder {
    private:
        ASTNode *objNameId;
    public:
        void setObjName(ASTNode *objName);

        NewNodeObject *build();
    };
};


#endif //DESIGN_1_NEWNODEOBJECT_H
