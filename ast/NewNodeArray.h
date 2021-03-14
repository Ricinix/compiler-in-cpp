//
// Created by laugh on 2021/3/14.
//

#ifndef DESIGN_1_NEWNODEARRAY_H
#define DESIGN_1_NEWNODEARRAY_H

#include "ASTNode.h"

class NewNodeArray : public ASTList {
private:
    std::vector<ASTNode *> elements;

    explicit NewNodeArray(std::vector<ASTNode *> &elementList);

public:
    std::string toString() const override;

    void genCode(IoUtil &ioUtil) override;

    class Builder {
    private:
        std::vector<ASTNode *> elements;
    public:
        void addElement(ASTNode *element);

        NewNodeArray *build();
    };
};


#endif //DESIGN_1_NEWNODEARRAY_H
