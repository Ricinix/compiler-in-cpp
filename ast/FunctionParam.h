//
// Created by laugh on 2021/3/11.
//

#ifndef DESIGN_1_FUNCTIONPARAM_H
#define DESIGN_1_FUNCTIONPARAM_H

#include "ASTNode.h"

class FunctionParam : public ASTLeaf{
public:
    explicit FunctionParam(Token *t);

    void genCode(IoUtil &ioUtil) override;
};


#endif //DESIGN_1_FUNCTIONPARAM_H
